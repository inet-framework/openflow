//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Packet_Out.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OFP_Packet_Out_m.h"

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

Register_Class(OFP_Packet_Out);

OFP_Packet_Out::OFP_Packet_Out(const char *name, int kind) : ::Open_Flow_Message(name,kind)
{
    this->buffer_id_var = 0;
    this->in_port_var = 0;
    actions_arraysize = 0;
    this->actions_var = 0;
    for (unsigned int i=0; i<0; i++)
        this->data_var[i] = 0;
}

OFP_Packet_Out::OFP_Packet_Out(const OFP_Packet_Out& other) : ::Open_Flow_Message(other)
{
    actions_arraysize = 0;
    this->actions_var = 0;
    copy(other);
}

OFP_Packet_Out::~OFP_Packet_Out()
{
    delete [] actions_var;
}

OFP_Packet_Out& OFP_Packet_Out::operator=(const OFP_Packet_Out& other)
{
    if (this==&other) return *this;
    ::Open_Flow_Message::operator=(other);
    copy(other);
    return *this;
}

void OFP_Packet_Out::copy(const OFP_Packet_Out& other)
{
    this->buffer_id_var = other.buffer_id_var;
    this->in_port_var = other.in_port_var;
    delete [] this->actions_var;
    this->actions_var = (other.actions_arraysize==0) ? NULL : new ofp_action_output[other.actions_arraysize];
    actions_arraysize = other.actions_arraysize;
    for (unsigned int i=0; i<actions_arraysize; i++)
        this->actions_var[i] = other.actions_var[i];
    for (unsigned int i=0; i<0; i++)
        this->data_var[i] = other.data_var[i];
}

void OFP_Packet_Out::parsimPack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimPack(b);
    doPacking(b,this->buffer_id_var);
    doPacking(b,this->in_port_var);
    b->pack(actions_arraysize);
    doPacking(b,this->actions_var,actions_arraysize);
    doPacking(b,this->data_var,0);
}

void OFP_Packet_Out::parsimUnpack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimUnpack(b);
    doUnpacking(b,this->buffer_id_var);
    doUnpacking(b,this->in_port_var);
    delete [] this->actions_var;
    b->unpack(actions_arraysize);
    if (actions_arraysize==0) {
        this->actions_var = 0;
    } else {
        this->actions_var = new ofp_action_output[actions_arraysize];
        doUnpacking(b,this->actions_var,actions_arraysize);
    }
    doUnpacking(b,this->data_var,0);
}

uint32_t OFP_Packet_Out::getBuffer_id() const
{
    return buffer_id_var;
}

void OFP_Packet_Out::setBuffer_id(uint32_t buffer_id)
{
    this->buffer_id_var = buffer_id;
}

uint32_t OFP_Packet_Out::getIn_port() const
{
    return in_port_var;
}

void OFP_Packet_Out::setIn_port(uint32_t in_port)
{
    this->in_port_var = in_port;
}

void OFP_Packet_Out::setActionsArraySize(unsigned int size)
{
    ofp_action_output *actions_var2 = (size==0) ? NULL : new ofp_action_output[size];
    unsigned int sz = actions_arraysize < size ? actions_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        actions_var2[i] = this->actions_var[i];
    actions_arraysize = size;
    delete [] this->actions_var;
    this->actions_var = actions_var2;
}

unsigned int OFP_Packet_Out::getActionsArraySize() const
{
    return actions_arraysize;
}

ofp_action_output& OFP_Packet_Out::getActions(unsigned int k)
{
    if (k>=actions_arraysize) throw cRuntimeError("Array of size %d indexed by %d", actions_arraysize, k);
    return actions_var[k];
}

void OFP_Packet_Out::setActions(unsigned int k, const ofp_action_output& actions)
{
    if (k>=actions_arraysize) throw cRuntimeError("Array of size %d indexed by %d", actions_arraysize, k);
    this->actions_var[k] = actions;
}

unsigned int OFP_Packet_Out::getDataArraySize() const
{
    return 0;
}

uint8_t OFP_Packet_Out::getData(unsigned int k) const
{
    if (k>=0) throw cRuntimeError("Array of size 0 indexed by %lu", (unsigned long)k);
    return data_var[k];
}

void OFP_Packet_Out::setData(unsigned int k, uint8_t data)
{
    if (k>=0) throw cRuntimeError("Array of size 0 indexed by %lu", (unsigned long)k);
    this->data_var[k] = data;
}

class OFP_Packet_OutDescriptor : public cClassDescriptor
{
  public:
    OFP_Packet_OutDescriptor();
    virtual ~OFP_Packet_OutDescriptor();

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

Register_ClassDescriptor(OFP_Packet_OutDescriptor);

OFP_Packet_OutDescriptor::OFP_Packet_OutDescriptor() : cClassDescriptor("OFP_Packet_Out", "Open_Flow_Message")
{
}

OFP_Packet_OutDescriptor::~OFP_Packet_OutDescriptor()
{
}

bool OFP_Packet_OutDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OFP_Packet_Out *>(obj)!=NULL;
}

const char *OFP_Packet_OutDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OFP_Packet_OutDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int OFP_Packet_OutDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *OFP_Packet_OutDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "buffer_id",
        "in_port",
        "actions",
        "data",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int OFP_Packet_OutDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "buffer_id")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "in_port")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "actions")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OFP_Packet_OutDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",
        "uint32_t",
        "ofp_action_output",
        "uint8_t",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *OFP_Packet_OutDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OFP_Packet_OutDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_Out *pp = (OFP_Packet_Out *)object; (void)pp;
    switch (field) {
        case 2: return pp->getActionsArraySize();
        case 3: return 0;
        default: return 0;
    }
}

std::string OFP_Packet_OutDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_Out *pp = (OFP_Packet_Out *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getBuffer_id());
        case 1: return ulong2string(pp->getIn_port());
        case 2: {std::stringstream out; out << pp->getActions(i); return out.str();}
        case 3: return ulong2string(pp->getData(i));
        default: return "";
    }
}

bool OFP_Packet_OutDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_Out *pp = (OFP_Packet_Out *)object; (void)pp;
    switch (field) {
        case 0: pp->setBuffer_id(string2ulong(value)); return true;
        case 1: pp->setIn_port(string2ulong(value)); return true;
        case 3: pp->setData(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *OFP_Packet_OutDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(ofp_action_output));
        default: return NULL;
    };
}

void *OFP_Packet_OutDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Packet_Out *pp = (OFP_Packet_Out *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getActions(i)); break;
        default: return NULL;
    }
}


