//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Packet_In.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OFP_Packet_In_m.h"

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

Register_Class(OFP_Packet_In);

OFP_Packet_In::OFP_Packet_In(const char *name, int kind) : ::Open_Flow_Message(name,kind)
{
    this->buffer_id_var = 0;
    this->total_len_var = 0;
    this->reason_var = 0;
}

OFP_Packet_In::OFP_Packet_In(const OFP_Packet_In& other) : ::Open_Flow_Message(other)
{
    copy(other);
}

OFP_Packet_In::~OFP_Packet_In()
{
}

OFP_Packet_In& OFP_Packet_In::operator=(const OFP_Packet_In& other)
{
    if (this==&other) return *this;
    ::Open_Flow_Message::operator=(other);
    copy(other);
    return *this;
}

void OFP_Packet_In::copy(const OFP_Packet_In& other)
{
    this->buffer_id_var = other.buffer_id_var;
    this->total_len_var = other.total_len_var;
    this->reason_var = other.reason_var;
    this->match_var = other.match_var;
}

void OFP_Packet_In::parsimPack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimPack(b);
    doPacking(b,this->buffer_id_var);
    doPacking(b,this->total_len_var);
    doPacking(b,this->reason_var);
    doPacking(b,this->match_var);
}

void OFP_Packet_In::parsimUnpack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimUnpack(b);
    doUnpacking(b,this->buffer_id_var);
    doUnpacking(b,this->total_len_var);
    doUnpacking(b,this->reason_var);
    doUnpacking(b,this->match_var);
}

uint32_t OFP_Packet_In::getBuffer_id() const
{
    return buffer_id_var;
}

void OFP_Packet_In::setBuffer_id(uint32_t buffer_id)
{
    this->buffer_id_var = buffer_id;
}

uint16_t OFP_Packet_In::getTotal_len() const
{
    return total_len_var;
}

void OFP_Packet_In::setTotal_len(uint16_t total_len)
{
    this->total_len_var = total_len;
}

uint8_t OFP_Packet_In::getReason() const
{
    return reason_var;
}

void OFP_Packet_In::setReason(uint8_t reason)
{
    this->reason_var = reason;
}

oxm_basic_match& OFP_Packet_In::getMatch()
{
    return match_var;
}

void OFP_Packet_In::setMatch(const oxm_basic_match& match)
{
    this->match_var = match;
}

class OFP_Packet_InDescriptor : public cClassDescriptor
{
  public:
    OFP_Packet_InDescriptor();
    virtual ~OFP_Packet_InDescriptor();

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

Register_ClassDescriptor(OFP_Packet_InDescriptor);

OFP_Packet_InDescriptor::OFP_Packet_InDescriptor() : cClassDescriptor("OFP_Packet_In", "Open_Flow_Message")
{
}

OFP_Packet_InDescriptor::~OFP_Packet_InDescriptor()
{
}

bool OFP_Packet_InDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OFP_Packet_In *>(obj)!=NULL;
}

const char *OFP_Packet_InDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OFP_Packet_InDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int OFP_Packet_InDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *OFP_Packet_InDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "buffer_id",
        "total_len",
        "reason",
        "match",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int OFP_Packet_InDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "buffer_id")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "total_len")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "reason")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "match")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OFP_Packet_InDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",
        "uint16_t",
        "uint8_t",
        "oxm_basic_match",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *OFP_Packet_InDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OFP_Packet_InDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_In *pp = (OFP_Packet_In *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OFP_Packet_InDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_In *pp = (OFP_Packet_In *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getBuffer_id());
        case 1: return ulong2string(pp->getTotal_len());
        case 2: return ulong2string(pp->getReason());
        case 3: {std::stringstream out; out << pp->getMatch(); return out.str();}
        default: return "";
    }
}

bool OFP_Packet_InDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_In *pp = (OFP_Packet_In *)object; (void)pp;
    switch (field) {
        case 0: pp->setBuffer_id(string2ulong(value)); return true;
        case 1: pp->setTotal_len(string2ulong(value)); return true;
        case 2: pp->setReason(string2ulong(value)); return true;
        default: return false;
    }
}

const char *OFP_Packet_InDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(oxm_basic_match));
        default: return NULL;
    };
}

void *OFP_Packet_InDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_In *pp = (OFP_Packet_In *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getMatch()); break;
        default: return NULL;
    }
}


