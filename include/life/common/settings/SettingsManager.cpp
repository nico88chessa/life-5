#include "SettingsManager.hpp"

#include <QString>
#include <QSettings>

#include <life/common/Traits.hpp>
#include <life/common/settings/descriptors/Descriptors.hpp>


using namespace dvlife;

MAYBE_UNUSED constexpr char DIGITAL_INPUT_NAME[] = "Name";
MAYBE_UNUSED constexpr char DIGITAL_INPUT_TYPE[] = "Type";
MAYBE_UNUSED constexpr char DIGITAL_INPUT_CHANNEL[] = "Channel";
MAYBE_UNUSED constexpr char DIGITAL_INPUT_INVERT_LOGIC[] = "InvertLogic";
MAYBE_UNUSED constexpr char DIGITAL_INPUT_DEVICE[] = "Device";
MAYBE_UNUSED constexpr char DIGITAL_INPUT_IS_ALARM[] = "IsAlarm";
MAYBE_UNUSED constexpr char DIGITAL_INPUT_IS_ALARM_INVERTED[] = "IsAlarmInverted";

MAYBE_UNUSED constexpr char DIGITAL_OUTPUT_NAME[] = "Name";
MAYBE_UNUSED constexpr char DIGITAL_OUTPUT_TYPE[] = "Type";
MAYBE_UNUSED constexpr char DIGITAL_OUTPUT_CHANNEL[] = "Channel";
MAYBE_UNUSED constexpr char DIGITAL_OUTPUT_INVERT_LOGIC[] = "InvertLogic";
MAYBE_UNUSED constexpr char DIGITAL_OUTPUT_DEVICE[] = "Device";
MAYBE_UNUSED constexpr char DIGITAL_OUTPUT_IS_ALARM[] = "IsAlarm";

MAYBE_UNUSED constexpr char ANALOG_INPUT_NAME[] = "Name";
MAYBE_UNUSED constexpr char ANALOG_INPUT_TYPE[] = "Type";
MAYBE_UNUSED constexpr char ANALOG_INPUT_CHANNEL[] = "Channel";
MAYBE_UNUSED constexpr char ANALOG_INPUT_DEVICE[] = "Device";
MAYBE_UNUSED constexpr char ANALOG_INPUT_IS_ALARM[] = "IsAlarm";
MAYBE_UNUSED constexpr char ANALOG_INPUT_GAIN[] = "Gain";
MAYBE_UNUSED constexpr char ANALOG_INPUT_OFFSET[] = "Offset";
MAYBE_UNUSED constexpr char ANALOG_INPUT_UNIT[] = "Unit";
MAYBE_UNUSED constexpr char ANALOG_INPUT_LOWER_LIMIT[] = "LowerLimit";
MAYBE_UNUSED constexpr char ANALOG_INPUT_UPPER_LIMIT[] = "UpperLimit";
MAYBE_UNUSED constexpr char ANALOG_INPUT_HYSTERESIS[] = "Hysteresis";


MAYBE_UNUSED static constexpr std::initializer_list<IOType> mandatoryIOTypes = {
    IOType::POWER,
    IOType::CYCLE,
    IOType::LASER_POWER, // per test
    IOType::GENERIC_ANALOG_INPUT // per test
};

constexpr bool isIOTypeMandatory(IOType type) {
    for (auto&& t: mandatoryIOTypes)
        if (t == type)
            return true;
    return false;
}

SettingsManager& SettingsManager::instance() {

    traceEnter;
    static SettingsManager sm = SettingsManager();
    traceExit;
    return sm;

}

SettingsManager::SettingsManager() :
    groups(), digitalInputs(), digitalOutputs(), analogInputs() {

    traceEnter;

    initialize();

    traceExit;

}

SettingsManager::~SettingsManager() { }

void SettingsManager::initialize() {

    traceEnter;
    // aggiungo tutti i gruppi
    addGroupFromDescriptor(AXIS_X_DESCR);
    addGroupFromDescriptor(AXIS_Z_DESCR);

    // aggiungo gli I/O obbligatori
    addMandatoryIO();

    // ora carico i parametri da file (almeno quelli presenti nel file)
    loadFromFile();

    // una volta caricati, faccio il flush su file (utile nel caso di inizializzazione del file di configurazione)
    flush();

    traceExit;

}

void SettingsManager::addGroupFromDescriptor(const SettingDescriptor& settingDescriptor) noexcept {

    traceEnter;

    using namespace dvlife::detail;

    SettingsGroupType type = settingDescriptor.groupType();
    if (groups.contains(type)) {
        traceInfo() << "Gruppo gia' presente.";
        return;
    }

    QString groupName = utils::EnumUtils::enumToName(type);
    groups.insert(type, Group(groupName, settingDescriptor.isMandatory()));
    Group& group = groups[type];

    // inizio a scorrere i parametri
    for (int i=0; i<settingDescriptor.size(); ++i) {

        MachineParameter p = settingDescriptor.getParameters()[i];

        /* NOTE NIC 04/04/2020
         * per questo trucco, vedere link https://en.cppreference.com/w/cpp/utility/variant/visit
         * il funzionamento del magico std::visit e' il seguente:
         * per ogni variant, viene ritornato il cast al tipo di valore che il variant contiene;
         * una volta fatto il cast, viene chiamata la funzione Callable (passata come primo
         * parametro dalla funzione visit stessa).
         * In questo caso quindi, la successione di eventi e' questa:
         * 1. passo il std::variant
         * 2. converte il std::variant ad un valore fra: int, double, ecc ecc
         * 3. il valore convertito passa alla funzione Callable (lambda in questo caso)
         * 4. la funzione lambda converte il valore a QVariant
         * La condizione if constexpr garantisce che la decisione del tipo viene fatta
         * a compile-time, non a runtime!!
         */
        auto setter = [](auto&& stdVariant, QVariant& v) {

            v = QVariant::fromValue(std::visit([](auto&& sv) -> QVariant {
                using T = std::decay_t<decltype(sv)>;
                if constexpr (std::is_same_v<T, int>)
                    return static_cast<int>(sv);
                else if constexpr (std::is_same_v<T, double>)
                    return static_cast<double>(sv);
                else if constexpr (std::is_same_v<T, MotorXKind>)
                    return QVariant::fromValue(static_cast<dvlife::MotorXKind>(sv));
                else if constexpr (std::is_same_v<T, AxisXFeedback>)
                    return QVariant::fromValue(static_cast<dvlife::AxisXFeedback>(sv));
            }, stdVariant));

        };
        setter(p.defaultValue, group.getParams()[p.key]);

    }

    traceExit;

}

void SettingsManager::addMandatoryIO() noexcept {

    traceEnter;
    for (auto&& mandatoryIO: mandatoryIOTypes) {

        if (isDigitalInputType(mandatoryIO)) {

            DigitalInputDescr d;
            d.setElementType(mandatoryIO);
            d.setName(utils::EnumUtils::enumToName(mandatoryIO));
            d.setMandatory(true);
            if (!this->addDigitalInput(d)) {

                /* TODO NIC 08/04/2020: gestione errore inserimento input digitali
                 * inventarsi qualcosa per segnalare il mancato inserimento dell'input
                 */

            }

        } else if (isDigitalOutputType(mandatoryIO)) {

            DigitalOutputDescr d;
            d.setElementType(mandatoryIO);
            d.setName(utils::EnumUtils::enumToName(mandatoryIO));
            d.setMandatory(true);
            if (!this->addDigitalOutput(d)) {

                /* TODO NIC 08/04/2020: gestione errore inserimento output digitali
                 * inventarsi qualcosa per segnalare il mancato inserimento dell'output
                 */

            }

        } else if (isAnalogInputType(mandatoryIO)) {

            AnalogInputDescr a;
            a.setElementType(mandatoryIO);
            a.setName(utils::EnumUtils::enumToName(mandatoryIO));
            a.setMandatory(true);
            if (!this->addAnalogInput(a)) {

                /* TODO NIC 08/04/2020: gestione errore inserimento input analogico
                 * inventarsi qualcosa per segnalare il mancato inserimento dell'input
                 */

            }

        }

    }

    traceExit;

}

void SettingsManager::loadFromFile() {

    traceEnter;

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION, PROJECT_NAME);

    // scorro i gruppi
    for (auto&& g: groups) {

        QStringView groupName = g.getName();

        // per ogni gruppo, prelevo i parametri
        auto&& paramsMap = g.getParams();
        for (auto&& paramKey: paramsMap.keys()) {

            QString stringKey = QString("%1/%2").arg(groupName).arg(paramKey);
            // valore da file o quello di default (caricato con il caricamento dei parametri)
            QVariant currentValue = settings.value(stringKey, paramsMap.value(paramKey));
            paramsMap[paramKey] = currentValue;

        }

    }

    // scorro gli input digitali
    int size = settings.beginReadArray(utils::EnumUtils::enumToName(SettingsGroupType::DIGITAL_INPUT));
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);

        auto device = utils::EnumUtils::nameToEnum<DeviceKey>(QLatin1String(settings.value(DIGITAL_INPUT_DEVICE).value<QString>().toLatin1()));
        auto channel = settings.value(DIGITAL_INPUT_CHANNEL).value<int>();
        if (channel == DIGITAL_INPUT_CHANNEL_NONE || device == DeviceKey::NONE)
            continue;
        auto type = utils::EnumUtils::nameToEnum<IOType>(QLatin1String(settings.value(DIGITAL_INPUT_TYPE).value<QString>().toLatin1()));
        QString name;
        if (utils::IOUtils::isGenericDigitalInput(type))
            name = settings.value(DIGITAL_INPUT_NAME).value<QString>();
        else
            name = utils::EnumUtils::enumToName(type);
        auto invertLogic = settings.value(DIGITAL_INPUT_INVERT_LOGIC).value<bool>();
        auto alarm = settings.value(DIGITAL_INPUT_IS_ALARM).value<bool>();
        auto alarmInverted = settings.value(DIGITAL_INPUT_IS_ALARM_INVERTED).value<bool>();
        bool mandatory = isIOTypeMandatory(type);

        if (!this->addDigitalInput(
                DigitalInputDescr(name, device, channel, invertLogic, alarm, alarmInverted, type, mandatory),
                true)) {

            /* TODO NIC 08/04/2020: gestione errore inserimento input digitali
             * inventarsi qualcosa per segnalare il mancato inserimento dell'input
             */

        }

    }
    settings.endArray();

    // scorro gli ouput digitali
    size = settings.beginReadArray(utils::EnumUtils::enumToName(SettingsGroupType::DIGITAL_OUTPUT));
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);

        auto device = utils::EnumUtils::nameToEnum<DeviceKey>(QLatin1String(settings.value(DIGITAL_OUTPUT_DEVICE).value<QString>().toLatin1()));
        auto channel = settings.value(DIGITAL_OUTPUT_CHANNEL).value<int>();
        if (channel == DIGITAL_OUTPUT_CHANNEL_NONE || device == DeviceKey::NONE)
            continue;
        auto type = utils::EnumUtils::nameToEnum<IOType>(QLatin1String(settings.value(DIGITAL_OUTPUT_TYPE).value<QString>().toLatin1()));
        QString name = settings.value(DIGITAL_OUTPUT_NAME).value<QString>();
        auto invertLogic = settings.value(DIGITAL_OUTPUT_INVERT_LOGIC).value<bool>();
        auto alarm = settings.value(DIGITAL_OUTPUT_IS_ALARM).value<bool>();
        bool mandatory = isIOTypeMandatory(type);

        if (!this->addDigitalOutput(
                DigitalOutputDescr(name, device, channel, invertLogic, alarm, type, mandatory),
                true)) {

            /* TODO NIC 08/04/2020: gestione errore inserimento output digitali
             * inventarsi qualcosa per segnalare il mancato inserimento dell'output
             */
        }

    }
    settings.endArray();

    // scorro gli input analogici
    size = settings.beginReadArray(utils::EnumUtils::enumToName(SettingsGroupType::ANALOG_INPUT));
    for (int i=0; i<size; ++i) {
        settings.setArrayIndex(i);
        auto name = settings.value(ANALOG_INPUT_NAME).value<QString>();
        auto type = settings.value(ANALOG_INPUT_TYPE).value<IOType>();
        auto channel = settings.value(ANALOG_INPUT_CHANNEL).value<int>();
        auto device = settings.value(ANALOG_INPUT_DEVICE).value<DeviceKey>();
        auto alarm = settings.value(ANALOG_INPUT_IS_ALARM).value<bool>();
        auto gain = settings.value(ANALOG_INPUT_GAIN).value<analogReal>();
        auto offset = settings.value(ANALOG_INPUT_OFFSET).value<analogReal>();
        auto unit = settings.value(ANALOG_INPUT_UNIT).value<QString>();
        auto lowerLimit = settings.value(ANALOG_INPUT_LOWER_LIMIT).value<analogReal>();
        auto upperLimit = settings.value(ANALOG_INPUT_UPPER_LIMIT).value<analogReal>();
        auto hysteresys = settings.value(ANALOG_INPUT_HYSTERESIS).value<analogReal>();
        bool mandatory = isIOTypeMandatory(IOType::GENERIC_ANALOG_INPUT);

        /* NOTE NIC 07/04/2020: caricamento ingressi analogici
         * ad oggi sono tutti ingressi generici; se in futuro ci sono ingressi fissi
         * allora bisogna utilizzare una gestione simile a quella degli ingressi generici
         * digitali;
         * la condizione qui sotto e' sempre soddisfatta, pero' se in futura cambia qualcosa,
         * la logica e' gia' pronta
         */
        if (!this->addAnalogInput(
                AnalogInputDescr(name, device, channel, alarm, gain, offset, unit, lowerLimit, upperLimit, hysteresys, type, mandatory),
                true)) {

            /* TODO NIC 08/04/2020: gestione errore inserimento input analogico
             * inventarsi qualcosa per segnalare il mancato inserimento dell'input
             */
        }


    }
    settings.endArray();

    traceExit;

}

bool SettingsManager::addDigitalInput(const DigitalInputDescr& d, bool overwriteIfExists) {

    traceEnter;

    if (utils::IOUtils::isGenericDigitalInput(d.getElementType())) {

        traceDebug() << "Nuovo input digitale di tipo generico " << utils::EnumUtils::enumToName(d.getElementType());;

        /* conto quanti input generici sto gestendo attualmente
         * inoltre, se trovo un digital input generico uguale, lo sovrascrivo; altrimenti procedo
         * per eventualmente aggiungerlo in coda (vedere uguaglianza nella classe DigitalInput)
         */

        DIKey key = static_cast<DIKey>(d.getElementType());
        int counter = 0;
        for (auto&& digitalInputKey: digitalInputs.keys()) {

            auto&& digitalInput = digitalInputs[digitalInputKey];
            // scorro solamente gli input digitali generici
            if (utils::IOUtils::isGenericDigitalInput(digitalInput.getElementType())) {

                /* la chiave viene cercata partendo da quella di default e incrementando man mano
                 * che ne vengono trovate di uguali; se infatti vengono rimosse delle chiavi, bisogna
                 * far si di coprire i 'buchi' lasciati liberi
                 */
                if (key == digitalInputKey)
                    ++key;

                if (digitalInput == d) {
                    // se l'input generico e' uguale
                    if (overwriteIfExists) {
                        // lo sovrascrivo (se il flag e' abilitato)
                        traceInfo() << "Trovato un input generico uguale a quello da inserire; lo sovrascrivo";
                        digitalInput = d;
                        return true;
                    } else {
                        // altrimenti non lo posso inserire
                        traceWarn() << QString("Impossibile inserire l'input digitale %1 - %2: gia' presente.").arg(utils::EnumUtils::enumToName(d.getElementType())).arg(d.getName());
                        return false;
                    }
                }

                counter++;
            }

        }

        if (!(counter < MAX_NUMBER_GENERIC_DIGITAL_INPUT)) {
            traceWarn() << "Raggiunto il limite di input digitali generici";
            return false;
        }

//        digitalInputKey key = static_cast<digitalInputKey>(d.getElementType()) + genericInputCounter;
        DigitalInputDescr newInput(d);
        this->digitalInputs.insert(key, newInput);
        traceDebug() << "Nuovo input digitale inserito con successo";

    } else {

        traceDebug() << "Nuovo input digitale " << utils::EnumUtils::enumToName(d.getElementType());;;
        DIKey key = static_cast<DIKey>(d.getElementType());

        if (this->digitalInputs.contains(key)) {

            if (!overwriteIfExists) {
                traceWarn() << QString("Impossibile inserire l'input digitale %1 - %2: gia' presente.").arg(utils::EnumUtils::enumToName(d.getElementType())).arg(d.getName());
                return false;
            } else
                digitalInputs[key] = DigitalInputDescr(d);

        } else {

            DigitalInputDescr newInput(d);
            this->digitalInputs.insert(key, newInput);
            traceDebug() << "Nuovo input digitale inserito con successo";

        }

    }

    traceExit;
    return true;

}

bool SettingsManager::addDigitalOutput(const DigitalOutputDescr& d, bool overwriteIfExists) {

    traceEnter;

    traceDebug() << "Nuovo output digitale " << utils::EnumUtils::enumToName(d.getElementType());;
    DOKey key = static_cast<DOKey>(d.getElementType());

    if (this->digitalOutputs.contains(key)) {

        if (!overwriteIfExists) {
            traceWarn() << "Output digitale gia' presente";
            return false;
        } else
            digitalOutputs[key] = DigitalOutputDescr(d);

    } else {

        DigitalOutputDescr newOutput(d);
        this->digitalOutputs.insert(key, newOutput);
        traceDebug() << "Nuovo output digitale inserito con successo";

    }

    traceExit;
    return true;

}

bool SettingsManager::addAnalogInput(const AnalogInputDescr& a, bool overwriteIfExists) {

    traceEnter;

    if (utils::IOUtils::isGenericAnalogInput(a.getElementType())) {

        traceDebug() << "Nuovo input analogico generico " << utils::EnumUtils::enumToName(a.getElementType());

        /* conto quanti input generici sto gestendo attualmente
         * inoltre, se trovo un analog input generico uguale, lo sovrascrivo; altrimenti procedo
         * per eventualmente aggiungerlo in coda (vedere uguaglianza nella classe AnalogInput)
         */

        AIKey key = static_cast<AIKey>(a.getElementType());
        int counter = 0;
        for (auto&& analogInputKey: analogInputs.keys()) {

            auto&& analogInput = analogInputs[analogInputKey];
            // scorro solamente gli input digitali generici
            if (utils::IOUtils::isGenericAnalogInput(analogInput.getElementType())) {

                if (key == analogInputKey)
                    ++key;

                if (analogInput == a) {
                    // se l'input generico e' uguale
                    if (overwriteIfExists) {
                        // lo sovrascrivo (se il flag e' abilitato)
                        traceInfo() << "Trovato un input generico uguale a quello da inserire; lo sovrascrivo";
                        analogInput = a;
                        return true;
                    } else {
                        // altrimenti non lo posso inserire
                        traceWarn() << QString("Impossibile inserire l'input analogico %1 - %2: gia' presente.").arg(utils::EnumUtils::enumToName(a.getElementType())).arg(a.getName());
                        return false;
                    }
                }

                counter++;
            }
        }

        if (!(counter < MAX_NUMBER_GENERIC_ANALOG_INPUT)) {
            traceWarn() << "Raggiunto il limite di input analogici generici";
            return false;
        }

//        analogInputKey key = static_cast<analogInputKey>(a.getElementType()) + genericInputCounter;
        traceDebug() << "Key dell'input analogico generico: " << key;
        AnalogInputDescr newInput(a);
        this->analogInputs.insert(key, newInput);
        traceDebug() << "Nuovo input analogico generico inserito con successo";

    } else {

        traceDebug() << "Nuovo input analogico " << utils::EnumUtils::enumToName(a.getElementType());
        AIKey key = static_cast<AIKey>(a.getElementType());

        if (this->analogInputs.contains(key)) {

            if (!overwriteIfExists) {
                traceWarn() << QString("Impossibile inserire l'input analogico %1 - %2: gia' presente.").arg(utils::EnumUtils::enumToName(a.getElementType())).arg(a.getName());
                return false;
            } else
                analogInputs[key] = AnalogInputDescr(a);

        } else {

            AnalogInputDescr newInput(a);
            this->analogInputs.insert(key, newInput);
            traceDebug() << "Nuovo input analogico inserito con successo";

        }

    }

    traceExit;
    return true;

}

bool SettingsManager::addDigitalInput(const DigitalInput& d) {

    traceEnter;
    bool res = this->addDigitalInput(DigitalInputDescr(d));
    traceExit;
    return res;

}

bool SettingsManager::addDigitalOutput(const DigitalOutput& d) {

    traceEnter;
    bool res = this->addDigitalOutput(DigitalOutputDescr(d));
    traceExit;
    return res;

}

bool SettingsManager::addAnalogInput(const AnalogInput& a) {

    traceEnter;
    bool res = this->addAnalogInput(AnalogInputDescr(a));
    traceExit;
    return res;

}

bool SettingsManager::removeDigitalInput(const DigitalInput& d) {

    traceEnter;

    DIKey keyFound = ENUM_INVALID;
    for (auto&& k: digitalInputs.keys())
        if (digitalInputs.value(k) == d)
            keyFound = k;

    bool deleteOK = false;
    if ( (keyFound != ENUM_INVALID) && (!digitalInputs.value(keyFound).isMandatory()) ) {
        // se ho trovato la key e l'ingresso non e' obbligatorio, allora posso eliminarlo
        digitalInputs.remove(keyFound);
        deleteOK = true;
        traceInfo() << "Rimozione input " << d.getName() << " avvenuto con successo";
    } else
        traceErr() << "Rimozione input " << d.getName() << " fallita. Input non trovato o obbligatorio";

    traceExit;
    return deleteOK;

}

bool SettingsManager::removeDigitalOutput(const DigitalOutput& d) {

    traceEnter;

    DOKey keyFound = ENUM_INVALID;
    for (auto&& k: digitalOutputs.keys())
        if (digitalOutputs.value(k) == d)
            keyFound = k;

    bool deleteOK = false;
    if ( (keyFound != ENUM_INVALID) && (!digitalOutputs.value(keyFound).isMandatory()) ) {
        // se ho trovato la key e l'uscita non e' obbligatorio, allora posso eliminarlo
        digitalOutputs.remove(keyFound);
        deleteOK = true;
        traceInfo() << "Rimozione output " << d.getName() << " avvenuto con successo";
    } else
        traceErr() << "Rimozione output " << d.getName() << " fallita. Output non trovato o obbligatorio";

    traceExit;
    return deleteOK;

}

bool SettingsManager::removeAnalogInput(const AnalogInput& a) {

    traceEnter;

    AIKey keyFound = ENUM_INVALID;
    for (auto&& k: analogInputs.keys())
        if (analogInputs.value(k) == a)
            keyFound = k;

    bool deleteOK = false;
    if ( (keyFound != ENUM_INVALID) && (!analogInputs.value(keyFound).isMandatory()) ) {
        // se ho trovato la key e l'ingresso non e' obbligatorio, allora posso eliminarlo
        analogInputs.remove(keyFound);
        deleteOK = true;
        traceInfo() << "Rimozione input " << a.getName() << " avvenuto con successo";
    } else
        traceErr() << "Rimozione input " << a.getName() << " fallita. Input non trovato o obbligatorio";

    traceExit;
    return deleteOK;

}

void SettingsManager::flush() {

    traceEnter;
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION, PROJECT_NAME);

    // scorro i gruppi
    for (auto&& g: groups) {

        QStringView groupName = g.getName();

        // sul file di configurazione scrivo i gruppi che sono abilitati oppure sono obbligatori
        if (g.isEnabled() || g.isMandatory()) {

            // per ogni gruppo, prelevo i parametri
            auto&& paramsMap = g.getParams();
            for (auto&& paramKey: paramsMap.keys()) {

                QString stringKey = QString("%1/%2").arg(groupName).arg(paramKey);
                QVariant currentValue = paramsMap.value(paramKey);

                settings.setValue(stringKey, currentValue);

            }

        } else {
            // gli altri li elimino
            settings.remove(groupName.toString());
        }

    }

    // scrittura input digitali
    settings.remove(utils::EnumUtils::enumToName(SettingsGroupType::DIGITAL_INPUT));
    settings.beginWriteArray(utils::EnumUtils::enumToName(SettingsGroupType::DIGITAL_INPUT));
    int i=0;
    for (DigitalInput input: digitalInputs) {
        settings.setArrayIndex(i++);
        settings.setValue(DIGITAL_INPUT_NAME, input.getName());
        settings.setValue(DIGITAL_INPUT_TYPE, utils::EnumUtils::enumToName(input.getElementType()));
        settings.setValue(DIGITAL_INPUT_CHANNEL, input.getChannel());
        settings.setValue(DIGITAL_INPUT_INVERT_LOGIC, input.isInvertLogic());
        settings.setValue(DIGITAL_INPUT_DEVICE, utils::EnumUtils::enumToName(input.getDevice()));
        settings.setValue(DIGITAL_INPUT_IS_ALARM, input.isAlarm());
        settings.setValue(DIGITAL_INPUT_IS_ALARM_INVERTED, input.isAlarmInverted());
    }
    settings.endArray();

    // scrittura output digitali
    settings.remove(utils::EnumUtils::enumToName(SettingsGroupType::DIGITAL_OUTPUT));
    settings.beginWriteArray(utils::EnumUtils::enumToName(SettingsGroupType::DIGITAL_OUTPUT));
    i=0;
    for (DigitalOutput output: digitalOutputs) {
        settings.setArrayIndex(i++);
        settings.setValue(DIGITAL_OUTPUT_NAME, output.getName());
        settings.setValue(DIGITAL_OUTPUT_TYPE, utils::EnumUtils::enumToName(output.getElementType()));
        settings.setValue(DIGITAL_OUTPUT_CHANNEL, output.getChannel());
        settings.setValue(DIGITAL_OUTPUT_INVERT_LOGIC, output.isInvertLogic());
        settings.setValue(DIGITAL_OUTPUT_DEVICE, utils::EnumUtils::enumToName(output.getDevice()));
        settings.setValue(DIGITAL_OUTPUT_IS_ALARM, output.isAlarm());
    }
    settings.endArray();

    // scrittura input analogici
    settings.remove(utils::EnumUtils::enumToName(SettingsGroupType::ANALOG_INPUT));
    settings.beginWriteArray(utils::EnumUtils::enumToName(SettingsGroupType::ANALOG_INPUT));
    i=0;

    /* NOTE NIC 08/04/2020: scrittura I/O analogici in file di configurazione
     * Per i valori, faccio un cast a double, altrimenti il file di configurazione non e' leggibile;
     * Qt usa i QVariant per i float, e scrivere un float QVariant nel file di configurazione risulta
     * cosi: @QVariant(....) = poco leggibile
     */
    for (AnalogInput analogInput: analogInputs) {
        settings.setArrayIndex(i++);
        settings.setValue(ANALOG_INPUT_NAME, analogInput.getName());
        settings.setValue(ANALOG_INPUT_TYPE, utils::EnumUtils::enumToName(analogInput.getElementType()));
        settings.setValue(ANALOG_INPUT_CHANNEL, analogInput.getChannel());
        settings.setValue(ANALOG_INPUT_DEVICE, utils::EnumUtils::enumToName(analogInput.getDevice()));
        settings.setValue(ANALOG_INPUT_IS_ALARM, analogInput.isAlarm());
        settings.setValue(ANALOG_INPUT_GAIN, static_cast<double>(analogInput.getGain()));
        settings.setValue(ANALOG_INPUT_OFFSET, static_cast<double>(analogInput.getOffset()));
        settings.setValue(ANALOG_INPUT_UNIT, analogInput.getUnit());
        settings.setValue(ANALOG_INPUT_LOWER_LIMIT, static_cast<double>(analogInput.getLowerLimit()));
        settings.setValue(ANALOG_INPUT_UPPER_LIMIT, static_cast<double>(analogInput.getUpperLimit()));
        settings.setValue(ANALOG_INPUT_HYSTERESIS, static_cast<double>(analogInput.getHysteresys()));
    }
    settings.endArray();

    settings.sync();

    traceExit;
}

void SettingsManager::restore() {

    traceEnter;

    traceDebug() << "Cancellazione mappe parametri";
    groups.clear();
    digitalInputs.clear();
    digitalOutputs.clear();
    analogInputs.clear();

    traceDebug() << "Reinizializzazione da file";
    initialize();

    traceExit;

}
