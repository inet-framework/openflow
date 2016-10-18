//
// Generated file, do not edit! Created by nedtool 4.6 from messages/HF_SyncReply.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HF_SyncReply_m.h"

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

Register_Class(HF_SyncReply);

HF_SyncReply::HF_SyncReply(const char *name, int kind) : ::cPacket(name,kind)
{
}

HF_SyncReply::HF_SyncReply(const HF_SyncReply& other) : ::cPacket(other)
{
    copy(other);
}

HF_SyncReply::~HF_SyncReply()
{
}

HF_SyncReply& HF_SyncReply::operator=(const HF_SyncReply& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HF_SyncReply::copy(const HF_SyncReply& other)
{
    this->controlChannel_var = other.controlChannel_var;
    this->dataChannel_var = other.dataChannel_var;
}

void HF_SyncReply::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->controlChannel_var);
    doPacking(b,this->dataChannel_var);
}

void HF_SyncReply::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->controlChannel_var);
    doUnpacking(b,this->dataChannel_var);
}

ControlChannel& HF_SyncReply::getControlChannel()
{
    return controlChannel_var;
}

void HF_SyncReply::setControlChannel(const ControlChannel& controlChannel)
{
    this->controlChannel_var = controlChannel;
}

DataChannel& HF_SyncReply::getDataChannel()
{
    return dataChannel_var;
}

void HF_SyncReply::setDataChannel(const DataChannel& dataChannel)
{
    this->dataChannel_var = dataChannel;
}

class HF_SyncReplyDescriptor : public cClassDescriptor
{
  public:
    HF_SyncReplyDescriptor();
    virtual ~HF_SyncReplyDescriptor();

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

Register_ClassDescriptor(HF_SyncReplyDescriptor);

HF_SyncReplyDescriptor::HF_SyncReplyDescriptor() : cClassDescriptor("HF_SyncReply", "cPacket")
{
}

HF_SyncReplyDescriptor::~HF_SyncReplyDescriptor()
{
}

bool HF_SyncReplyDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<HF_SyncReply *>(obj)!=NULL;
}

const char *HF_SyncReplyDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HF_SyncReplyDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int HF_SyncReplyDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *HF_SyncReplyDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "controlChannel",
        "dataChannel",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int HF_SyncReplyDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "controlChannel")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataChannel")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *HF_SyncReplyDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "ControlChannel",
        "DataChannel",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *HF_SyncReplyDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int HF_SyncReplyDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HF_SyncReply *pp = (HF_SyncReply *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string HF_SyncReplyDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    HF_SyncReply *pp = (HF_SyncReply *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getControlChannel(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDataChannel(); return out.str();}
        default: return "";
    }
}

bool HF_SyncReplyDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HF_SyncReply *pp = (HF_SyncReply *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *HF_SyncReplyDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(ControlChannel));
        case 1: return opp_typename(typeid(DataChannel));
        default: return NULL;
    };
}

void *HF_SyncReplyDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HF_SyncReply *pp = (HF_SyncReply *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getControlChannel()); break;
        case 1: return (void *)(&pp->getDataChannel()); break;
        default: return NULL;
    }
}


