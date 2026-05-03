//
// Generated file, do not edit! Created by opp_msgtool 6.0 from LinDataFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "LinDataFrame_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(LinBreakSignal)

LinBreakSignal::LinBreakSignal(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

LinBreakSignal::LinBreakSignal(const LinBreakSignal& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

LinBreakSignal::~LinBreakSignal()
{
}

LinBreakSignal& LinBreakSignal::operator=(const LinBreakSignal& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void LinBreakSignal::copy(const LinBreakSignal& other)
{
    this->sourceAddr = other.sourceAddr;
    this->ingressPortIndex = other.ingressPortIndex;
    this->duration = other.duration;
}

void LinBreakSignal::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->ingressPortIndex);
    doParsimPacking(b,this->duration);
}

void LinBreakSignal::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->ingressPortIndex);
    doParsimUnpacking(b,this->duration);
}

int LinBreakSignal::getSourceAddr() const
{
    return this->sourceAddr;
}

void LinBreakSignal::setSourceAddr(int sourceAddr)
{
    this->sourceAddr = sourceAddr;
}

int LinBreakSignal::getIngressPortIndex() const
{
    return this->ingressPortIndex;
}

void LinBreakSignal::setIngressPortIndex(int ingressPortIndex)
{
    this->ingressPortIndex = ingressPortIndex;
}

double LinBreakSignal::getDuration() const
{
    return this->duration;
}

void LinBreakSignal::setDuration(double duration)
{
    this->duration = duration;
}

class LinBreakSignalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceAddr,
        FIELD_ingressPortIndex,
        FIELD_duration,
    };
  public:
    LinBreakSignalDescriptor();
    virtual ~LinBreakSignalDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LinBreakSignalDescriptor)

LinBreakSignalDescriptor::LinBreakSignalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(LinBreakSignal)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

LinBreakSignalDescriptor::~LinBreakSignalDescriptor()
{
    delete[] propertyNames;
}

bool LinBreakSignalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinBreakSignal *>(obj)!=nullptr;
}

const char **LinBreakSignalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinBreakSignalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinBreakSignalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LinBreakSignalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceAddr
        FD_ISEDITABLE,    // FIELD_ingressPortIndex
        FD_ISEDITABLE,    // FIELD_duration
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LinBreakSignalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddr",
        "ingressPortIndex",
        "duration",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LinBreakSignalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ingressPortIndex") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "duration") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LinBreakSignalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceAddr
        "int",    // FIELD_ingressPortIndex
        "double",    // FIELD_duration
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LinBreakSignalDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LinBreakSignalDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LinBreakSignalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LinBreakSignalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinBreakSignal'", field);
    }
}

const char *LinBreakSignalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinBreakSignalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return long2string(pp->getSourceAddr());
        case FIELD_ingressPortIndex: return long2string(pp->getIngressPortIndex());
        case FIELD_duration: return double2string(pp->getDuration());
        default: return "";
    }
}

void LinBreakSignalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(string2long(value)); break;
        case FIELD_ingressPortIndex: pp->setIngressPortIndex(string2long(value)); break;
        case FIELD_duration: pp->setDuration(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinBreakSignal'", field);
    }
}

omnetpp::cValue LinBreakSignalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return pp->getSourceAddr();
        case FIELD_ingressPortIndex: return pp->getIngressPortIndex();
        case FIELD_duration: return pp->getDuration();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinBreakSignal' as cValue -- field index out of range?", field);
    }
}

void LinBreakSignalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ingressPortIndex: pp->setIngressPortIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_duration: pp->setDuration(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinBreakSignal'", field);
    }
}

const char *LinBreakSignalDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LinBreakSignalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinBreakSignalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinBreakSignal *pp = omnetpp::fromAnyPtr<LinBreakSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinBreakSignal'", field);
    }
}

Register_Class(LinHeader)

LinHeader::LinHeader(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

LinHeader::LinHeader(const LinHeader& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

LinHeader::~LinHeader()
{
}

LinHeader& LinHeader::operator=(const LinHeader& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void LinHeader::copy(const LinHeader& other)
{
    this->sourceAddr = other.sourceAddr;
    this->ingressPortIndex = other.ingressPortIndex;
    this->frameId = other.frameId;
    this->pid = other.pid;
    this->syncByte = other.syncByte;
}

void LinHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->ingressPortIndex);
    doParsimPacking(b,this->frameId);
    doParsimPacking(b,this->pid);
    doParsimPacking(b,this->syncByte);
}

void LinHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->ingressPortIndex);
    doParsimUnpacking(b,this->frameId);
    doParsimUnpacking(b,this->pid);
    doParsimUnpacking(b,this->syncByte);
}

int LinHeader::getSourceAddr() const
{
    return this->sourceAddr;
}

void LinHeader::setSourceAddr(int sourceAddr)
{
    this->sourceAddr = sourceAddr;
}

int LinHeader::getIngressPortIndex() const
{
    return this->ingressPortIndex;
}

void LinHeader::setIngressPortIndex(int ingressPortIndex)
{
    this->ingressPortIndex = ingressPortIndex;
}

int LinHeader::getFrameId() const
{
    return this->frameId;
}

void LinHeader::setFrameId(int frameId)
{
    this->frameId = frameId;
}

int LinHeader::getPid() const
{
    return this->pid;
}

void LinHeader::setPid(int pid)
{
    this->pid = pid;
}

char LinHeader::getSyncByte() const
{
    return this->syncByte;
}

void LinHeader::setSyncByte(char syncByte)
{
    this->syncByte = syncByte;
}

class LinHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceAddr,
        FIELD_ingressPortIndex,
        FIELD_frameId,
        FIELD_pid,
        FIELD_syncByte,
    };
  public:
    LinHeaderDescriptor();
    virtual ~LinHeaderDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LinHeaderDescriptor)

LinHeaderDescriptor::LinHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(LinHeader)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

LinHeaderDescriptor::~LinHeaderDescriptor()
{
    delete[] propertyNames;
}

bool LinHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinHeader *>(obj)!=nullptr;
}

const char **LinHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LinHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceAddr
        FD_ISEDITABLE,    // FIELD_ingressPortIndex
        FD_ISEDITABLE,    // FIELD_frameId
        FD_ISEDITABLE,    // FIELD_pid
        FD_ISEDITABLE,    // FIELD_syncByte
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LinHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddr",
        "ingressPortIndex",
        "frameId",
        "pid",
        "syncByte",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LinHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ingressPortIndex") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "frameId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "pid") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "syncByte") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LinHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceAddr
        "int",    // FIELD_ingressPortIndex
        "int",    // FIELD_frameId
        "int",    // FIELD_pid
        "char",    // FIELD_syncByte
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LinHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LinHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LinHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LinHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinHeader'", field);
    }
}

const char *LinHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return long2string(pp->getSourceAddr());
        case FIELD_ingressPortIndex: return long2string(pp->getIngressPortIndex());
        case FIELD_frameId: return long2string(pp->getFrameId());
        case FIELD_pid: return long2string(pp->getPid());
        case FIELD_syncByte: return long2string(pp->getSyncByte());
        default: return "";
    }
}

void LinHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(string2long(value)); break;
        case FIELD_ingressPortIndex: pp->setIngressPortIndex(string2long(value)); break;
        case FIELD_frameId: pp->setFrameId(string2long(value)); break;
        case FIELD_pid: pp->setPid(string2long(value)); break;
        case FIELD_syncByte: pp->setSyncByte(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinHeader'", field);
    }
}

omnetpp::cValue LinHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return pp->getSourceAddr();
        case FIELD_ingressPortIndex: return pp->getIngressPortIndex();
        case FIELD_frameId: return pp->getFrameId();
        case FIELD_pid: return pp->getPid();
        case FIELD_syncByte: return pp->getSyncByte();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinHeader' as cValue -- field index out of range?", field);
    }
}

void LinHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ingressPortIndex: pp->setIngressPortIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_frameId: pp->setFrameId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_pid: pp->setPid(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_syncByte: pp->setSyncByte(omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinHeader'", field);
    }
}

const char *LinHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LinHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinHeader *pp = omnetpp::fromAnyPtr<LinHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinHeader'", field);
    }
}

Register_Class(LinResponse)

LinResponse::LinResponse(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

LinResponse::LinResponse(const LinResponse& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

LinResponse::~LinResponse()
{
}

LinResponse& LinResponse::operator=(const LinResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void LinResponse::copy(const LinResponse& other)
{
    this->sourceAddr = other.sourceAddr;
    this->ingressPortIndex = other.ingressPortIndex;
    this->frameId = other.frameId;
    this->dataLength = other.dataLength;
    for (size_t i = 0; i < 8; i++) {
        this->data[i] = other.data[i];
    }
    this->checksum = other.checksum;
    this->collision = other.collision;
}

void LinResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->ingressPortIndex);
    doParsimPacking(b,this->frameId);
    doParsimPacking(b,this->dataLength);
    doParsimArrayPacking(b,this->data,8);
    doParsimPacking(b,this->checksum);
    doParsimPacking(b,this->collision);
}

void LinResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->ingressPortIndex);
    doParsimUnpacking(b,this->frameId);
    doParsimUnpacking(b,this->dataLength);
    doParsimArrayUnpacking(b,this->data,8);
    doParsimUnpacking(b,this->checksum);
    doParsimUnpacking(b,this->collision);
}

int LinResponse::getSourceAddr() const
{
    return this->sourceAddr;
}

void LinResponse::setSourceAddr(int sourceAddr)
{
    this->sourceAddr = sourceAddr;
}

int LinResponse::getIngressPortIndex() const
{
    return this->ingressPortIndex;
}

void LinResponse::setIngressPortIndex(int ingressPortIndex)
{
    this->ingressPortIndex = ingressPortIndex;
}

int LinResponse::getFrameId() const
{
    return this->frameId;
}

void LinResponse::setFrameId(int frameId)
{
    this->frameId = frameId;
}

int LinResponse::getDataLength() const
{
    return this->dataLength;
}

void LinResponse::setDataLength(int dataLength)
{
    this->dataLength = dataLength;
}

size_t LinResponse::getDataArraySize() const
{
    return 8;
}

char LinResponse::getData(size_t k) const
{
    if (k >= 8) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)8, (unsigned long)k);
    return this->data[k];
}

void LinResponse::setData(size_t k, char data)
{
    if (k >= 8) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)8, (unsigned long)k);
    this->data[k] = data;
}

char LinResponse::getChecksum() const
{
    return this->checksum;
}

void LinResponse::setChecksum(char checksum)
{
    this->checksum = checksum;
}

bool LinResponse::getCollision() const
{
    return this->collision;
}

void LinResponse::setCollision(bool collision)
{
    this->collision = collision;
}

class LinResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceAddr,
        FIELD_ingressPortIndex,
        FIELD_frameId,
        FIELD_dataLength,
        FIELD_data,
        FIELD_checksum,
        FIELD_collision,
    };
  public:
    LinResponseDescriptor();
    virtual ~LinResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LinResponseDescriptor)

LinResponseDescriptor::LinResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(LinResponse)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

LinResponseDescriptor::~LinResponseDescriptor()
{
    delete[] propertyNames;
}

bool LinResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinResponse *>(obj)!=nullptr;
}

const char **LinResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int LinResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceAddr
        FD_ISEDITABLE,    // FIELD_ingressPortIndex
        FD_ISEDITABLE,    // FIELD_frameId
        FD_ISEDITABLE,    // FIELD_dataLength
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_data
        FD_ISEDITABLE,    // FIELD_checksum
        FD_ISEDITABLE,    // FIELD_collision
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *LinResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddr",
        "ingressPortIndex",
        "frameId",
        "dataLength",
        "data",
        "checksum",
        "collision",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int LinResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ingressPortIndex") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "frameId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dataLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "data") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "checksum") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "collision") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *LinResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceAddr
        "int",    // FIELD_ingressPortIndex
        "int",    // FIELD_frameId
        "int",    // FIELD_dataLength
        "char",    // FIELD_data
        "char",    // FIELD_checksum
        "bool",    // FIELD_collision
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **LinResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LinResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LinResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        case FIELD_data: return 8;
        default: return 0;
    }
}

void LinResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinResponse'", field);
    }
}

const char *LinResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return long2string(pp->getSourceAddr());
        case FIELD_ingressPortIndex: return long2string(pp->getIngressPortIndex());
        case FIELD_frameId: return long2string(pp->getFrameId());
        case FIELD_dataLength: return long2string(pp->getDataLength());
        case FIELD_data: return long2string(pp->getData(i));
        case FIELD_checksum: return long2string(pp->getChecksum());
        case FIELD_collision: return bool2string(pp->getCollision());
        default: return "";
    }
}

void LinResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(string2long(value)); break;
        case FIELD_ingressPortIndex: pp->setIngressPortIndex(string2long(value)); break;
        case FIELD_frameId: pp->setFrameId(string2long(value)); break;
        case FIELD_dataLength: pp->setDataLength(string2long(value)); break;
        case FIELD_data: pp->setData(i,string2long(value)); break;
        case FIELD_checksum: pp->setChecksum(string2long(value)); break;
        case FIELD_collision: pp->setCollision(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinResponse'", field);
    }
}

omnetpp::cValue LinResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return pp->getSourceAddr();
        case FIELD_ingressPortIndex: return pp->getIngressPortIndex();
        case FIELD_frameId: return pp->getFrameId();
        case FIELD_dataLength: return pp->getDataLength();
        case FIELD_data: return pp->getData(i);
        case FIELD_checksum: return pp->getChecksum();
        case FIELD_collision: return pp->getCollision();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinResponse' as cValue -- field index out of range?", field);
    }
}

void LinResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ingressPortIndex: pp->setIngressPortIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_frameId: pp->setFrameId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dataLength: pp->setDataLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_data: pp->setData(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_checksum: pp->setChecksum(omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_collision: pp->setCollision(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinResponse'", field);
    }
}

const char *LinResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LinResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinResponse *pp = omnetpp::fromAnyPtr<LinResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinResponse'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

