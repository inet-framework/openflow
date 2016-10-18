//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Features_Reply.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OFP_Features_Reply_m.h"

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

Register_Class(OFP_Features_Reply);

OFP_Features_Reply::OFP_Features_Reply(const char *name, int kind) : ::Open_Flow_Message(name,kind)
{
    this->datapath_id_var = 0;
    this->n_buffers_var = 0;
    this->n_tables_var = 0;
    this->capabilities_var = 0;
    this->reserved_var = 0;
    ports_arraysize = 0;
    this->ports_var = 0;
}

OFP_Features_Reply::OFP_Features_Reply(const OFP_Features_Reply& other) : ::Open_Flow_Message(other)
{
    ports_arraysize = 0;
    this->ports_var = 0;
    copy(other);
}

OFP_Features_Reply::~OFP_Features_Reply()
{
    delete [] ports_var;
}

OFP_Features_Reply& OFP_Features_Reply::operator=(const OFP_Features_Reply& other)
{
    if (this==&other) return *this;
    ::Open_Flow_Message::operator=(other);
    copy(other);
    return *this;
}

void OFP_Features_Reply::copy(const OFP_Features_Reply& other)
{
    this->datapath_id_var = other.datapath_id_var;
    this->n_buffers_var = other.n_buffers_var;
    this->n_tables_var = other.n_tables_var;
    this->capabilities_var = other.capabilities_var;
    this->reserved_var = other.reserved_var;
    delete [] this->ports_var;
    this->ports_var = (other.ports_arraysize==0) ? NULL : new uint32_t[other.ports_arraysize];
    ports_arraysize = other.ports_arraysize;
    for (unsigned int i=0; i<ports_arraysize; i++)
        this->ports_var[i] = other.ports_var[i];
}

void OFP_Features_Reply::parsimPack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimPack(b);
    doPacking(b,this->datapath_id_var);
    doPacking(b,this->n_buffers_var);
    doPacking(b,this->n_tables_var);
    doPacking(b,this->capabilities_var);
    doPacking(b,this->reserved_var);
    b->pack(ports_arraysize);
    doPacking(b,this->ports_var,ports_arraysize);
}

void OFP_Features_Reply::parsimUnpack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimUnpack(b);
    doUnpacking(b,this->datapath_id_var);
    doUnpacking(b,this->n_buffers_var);
    doUnpacking(b,this->n_tables_var);
    doUnpacking(b,this->capabilities_var);
    doUnpacking(b,this->reserved_var);
    delete [] this->ports_var;
    b->unpack(ports_arraysize);
    if (ports_arraysize==0) {
        this->ports_var = 0;
    } else {
        this->ports_var = new uint32_t[ports_arraysize];
        doUnpacking(b,this->ports_var,ports_arraysize);
    }
}

const char * OFP_Features_Reply::getDatapath_id() const
{
    return datapath_id_var.c_str();
}

void OFP_Features_Reply::setDatapath_id(const char * datapath_id)
{
    this->datapath_id_var = datapath_id;
}

uint32_t OFP_Features_Reply::getN_buffers() const
{
    return n_buffers_var;
}

void OFP_Features_Reply::setN_buffers(uint32_t n_buffers)
{
    this->n_buffers_var = n_buffers;
}

uint8_t OFP_Features_Reply::getN_tables() const
{
    return n_tables_var;
}

void OFP_Features_Reply::setN_tables(uint8_t n_tables)
{
    this->n_tables_var = n_tables;
}

uint32_t OFP_Features_Reply::getCapabilities() const
{
    return capabilities_var;
}

void OFP_Features_Reply::setCapabilities(uint32_t capabilities)
{
    this->capabilities_var = capabilities;
}

uint32_t OFP_Features_Reply::getReserved() const
{
    return reserved_var;
}

void OFP_Features_Reply::setReserved(uint32_t reserved)
{
    this->reserved_var = reserved;
}

void OFP_Features_Reply::setPortsArraySize(unsigned int size)
{
    uint32_t *ports_var2 = (size==0) ? NULL : new uint32_t[size];
    unsigned int sz = ports_arraysize < size ? ports_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        ports_var2[i] = this->ports_var[i];
    for (unsigned int i=sz; i<size; i++)
        ports_var2[i] = 0;
    ports_arraysize = size;
    delete [] this->ports_var;
    this->ports_var = ports_var2;
}

unsigned int OFP_Features_Reply::getPortsArraySize() const
{
    return ports_arraysize;
}

uint32_t OFP_Features_Reply::getPorts(unsigned int k) const
{
    if (k>=ports_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ports_arraysize, k);
    return ports_var[k];
}

void OFP_Features_Reply::setPorts(unsigned int k, uint32_t ports)
{
    if (k>=ports_arraysize) throw cRuntimeError("Array of size %d indexed by %d", ports_arraysize, k);
    this->ports_var[k] = ports;
}

class OFP_Features_ReplyDescriptor : public cClassDescriptor
{
  public:
    OFP_Features_ReplyDescriptor();
    virtual ~OFP_Features_ReplyDescriptor();

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

Register_ClassDescriptor(OFP_Features_ReplyDescriptor);

OFP_Features_ReplyDescriptor::OFP_Features_ReplyDescriptor() : cClassDescriptor("OFP_Features_Reply", "Open_Flow_Message")
{
}

OFP_Features_ReplyDescriptor::~OFP_Features_ReplyDescriptor()
{
}

bool OFP_Features_ReplyDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OFP_Features_Reply *>(obj)!=NULL;
}

const char *OFP_Features_ReplyDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OFP_Features_ReplyDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int OFP_Features_ReplyDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *OFP_Features_ReplyDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "datapath_id",
        "n_buffers",
        "n_tables",
        "capabilities",
        "reserved",
        "ports",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int OFP_Features_ReplyDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "datapath_id")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "n_buffers")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "n_tables")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "capabilities")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "reserved")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "ports")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OFP_Features_ReplyDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "uint32_t",
        "uint8_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *OFP_Features_ReplyDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OFP_Features_ReplyDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Features_Reply *pp = (OFP_Features_Reply *)object; (void)pp;
    switch (field) {
        case 5: return pp->getPortsArraySize();
        default: return 0;
    }
}

std::string OFP_Features_ReplyDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Features_Reply *pp = (OFP_Features_Reply *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDatapath_id());
        case 1: return ulong2string(pp->getN_buffers());
        case 2: return ulong2string(pp->getN_tables());
        case 3: return ulong2string(pp->getCapabilities());
        case 4: return ulong2string(pp->getReserved());
        case 5: return ulong2string(pp->getPorts(i));
        default: return "";
    }
}

bool OFP_Features_ReplyDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Features_Reply *pp = (OFP_Features_Reply *)object; (void)pp;
    switch (field) {
        case 0: pp->setDatapath_id((value)); return true;
        case 1: pp->setN_buffers(string2ulong(value)); return true;
        case 2: pp->setN_tables(string2ulong(value)); return true;
        case 3: pp->setCapabilities(string2ulong(value)); return true;
        case 4: pp->setReserved(string2ulong(value)); return true;
        case 5: pp->setPorts(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *OFP_Features_ReplyDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *OFP_Features_ReplyDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Features_Reply *pp = (OFP_Features_Reply *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


