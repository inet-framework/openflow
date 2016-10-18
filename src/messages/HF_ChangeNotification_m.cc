//
// Generated file, do not edit! Created by nedtool 4.6 from messages/HF_ChangeNotification.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HF_ChangeNotification_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(HF_ChangeNotification);

HF_ChangeNotification::HF_ChangeNotification(const char *name, int kind) : ::cPacket(name,kind)
{
}

HF_ChangeNotification::HF_ChangeNotification(const HF_ChangeNotification& other) : ::cPacket(other)
{
    copy(other);
}

HF_ChangeNotification::~HF_ChangeNotification()
{
}

HF_ChangeNotification& HF_ChangeNotification::operator=(const HF_ChangeNotification& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HF_ChangeNotification::copy(const HF_ChangeNotification& other)
{
    this->entry_var = other.entry_var;
}

void HF_ChangeNotification::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->entry_var);
}

void HF_ChangeNotification::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->entry_var);
}

DataChannelEntry& HF_ChangeNotification::getEntry()
{
    return entry_var;
}

void HF_ChangeNotification::setEntry(const DataChannelEntry& entry)
{
    this->entry_var = entry;
}

class HF_ChangeNotificationDescriptor : public cClassDescriptor
{
  public:
    HF_ChangeNotificationDescriptor();
    virtual ~HF_ChangeNotificationDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(HF_ChangeNotificationDescriptor);

HF_ChangeNotificationDescriptor::HF_ChangeNotificationDescriptor() : cClassDescriptor("HF_ChangeNotification", "cPacket")
{
}

HF_ChangeNotificationDescriptor::~HF_ChangeNotificationDescriptor()
{
}

bool HF_ChangeNotificationDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<HF_ChangeNotification *>(obj)!=NULL;
}

const char *HF_ChangeNotificationDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HF_ChangeNotificationDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int HF_ChangeNotificationDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *HF_ChangeNotificationDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "entry",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int HF_ChangeNotificationDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "entry")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *HF_ChangeNotificationDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "DataChannelEntry",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *HF_ChangeNotificationDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int HF_ChangeNotificationDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HF_ChangeNotification *pp = (HF_ChangeNotification *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string HF_ChangeNotificationDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    HF_ChangeNotification *pp = (HF_ChangeNotification *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getEntry(); return out.str();}
        default: return "";
    }
}

bool HF_ChangeNotificationDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HF_ChangeNotification *pp = (HF_ChangeNotification *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *HF_ChangeNotificationDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(DataChannelEntry));
        default: return NULL;
    };
}

void *HF_ChangeNotificationDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HF_ChangeNotification *pp = (HF_ChangeNotification *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getEntry()); break;
        default: return NULL;
    }
}


