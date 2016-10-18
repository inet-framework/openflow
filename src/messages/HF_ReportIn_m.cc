//
// Generated file, do not edit! Created by nedtool 4.6 from messages/HF_ReportIn.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HF_ReportIn_m.h"

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

Register_Class(HF_ReportIn);

HF_ReportIn::HF_ReportIn(const char *name, int kind) : ::cPacket(name,kind)
{
    this->controllerId_var = 0;
}

HF_ReportIn::HF_ReportIn(const HF_ReportIn& other) : ::cPacket(other)
{
    copy(other);
}

HF_ReportIn::~HF_ReportIn()
{
}

HF_ReportIn& HF_ReportIn::operator=(const HF_ReportIn& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HF_ReportIn::copy(const HF_ReportIn& other)
{
    this->controllerId_var = other.controllerId_var;
    this->switchInfoList_var = other.switchInfoList_var;
}

void HF_ReportIn::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->controllerId_var);
    doPacking(b,this->switchInfoList_var);
}

void HF_ReportIn::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->controllerId_var);
    doUnpacking(b,this->switchInfoList_var);
}

const char * HF_ReportIn::getControllerId() const
{
    return controllerId_var.c_str();
}

void HF_ReportIn::setControllerId(const char * controllerId)
{
    this->controllerId_var = controllerId;
}

SwitchInfoList& HF_ReportIn::getSwitchInfoList()
{
    return switchInfoList_var;
}

void HF_ReportIn::setSwitchInfoList(const SwitchInfoList& switchInfoList)
{
    this->switchInfoList_var = switchInfoList;
}

class HF_ReportInDescriptor : public cClassDescriptor
{
  public:
    HF_ReportInDescriptor();
    virtual ~HF_ReportInDescriptor();

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

Register_ClassDescriptor(HF_ReportInDescriptor);

HF_ReportInDescriptor::HF_ReportInDescriptor() : cClassDescriptor("HF_ReportIn", "cPacket")
{
}

HF_ReportInDescriptor::~HF_ReportInDescriptor()
{
}

bool HF_ReportInDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<HF_ReportIn *>(obj)!=NULL;
}

const char *HF_ReportInDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HF_ReportInDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HF_ReportInDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *HF_ReportInDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "controllerId",
        "switchInfoList",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int HF_ReportInDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "controllerId")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "switchInfoList")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *HF_ReportInDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "SwitchInfoList",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *HF_ReportInDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int HF_ReportInDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HF_ReportIn *pp = (HF_ReportIn *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string HF_ReportInDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    HF_ReportIn *pp = (HF_ReportIn *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getControllerId());
        case 1: {std::stringstream out; out << pp->getSwitchInfoList(); return out.str();}
        default: return "";
    }
}

bool HF_ReportInDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HF_ReportIn *pp = (HF_ReportIn *)object; (void)pp;
    switch (field) {
        case 0: pp->setControllerId((value)); return true;
        default: return false;
    }
}

const char *HF_ReportInDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(SwitchInfoList));
        default: return NULL;
    };
}

void *HF_ReportInDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HF_ReportIn *pp = (HF_ReportIn *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSwitchInfoList()); break;
        default: return NULL;
    }
}


