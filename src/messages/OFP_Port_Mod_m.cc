//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Port_Mod.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OFP_Port_Mod_m.h"

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

Register_Class(OFP_Port_Mod);

OFP_Port_Mod::OFP_Port_Mod(const char *name, int kind) : ::Open_Flow_Message(name,kind)
{
    this->port_no_var = 0;
    for (unsigned int i=0; i<6; i++)
        this->hw_addr_var[i] = 0;
    this->config_var = 0;
    this->mask_var = 0;
    this->advertise_var = 0;
}

OFP_Port_Mod::OFP_Port_Mod(const OFP_Port_Mod& other) : ::Open_Flow_Message(other)
{
    copy(other);
}

OFP_Port_Mod::~OFP_Port_Mod()
{
}

OFP_Port_Mod& OFP_Port_Mod::operator=(const OFP_Port_Mod& other)
{
    if (this==&other) return *this;
    ::Open_Flow_Message::operator=(other);
    copy(other);
    return *this;
}

void OFP_Port_Mod::copy(const OFP_Port_Mod& other)
{
    this->port_no_var = other.port_no_var;
    for (unsigned int i=0; i<6; i++)
        this->hw_addr_var[i] = other.hw_addr_var[i];
    this->config_var = other.config_var;
    this->mask_var = other.mask_var;
    this->advertise_var = other.advertise_var;
}

void OFP_Port_Mod::parsimPack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimPack(b);
    doPacking(b,this->port_no_var);
    doPacking(b,this->hw_addr_var,6);
    doPacking(b,this->config_var);
    doPacking(b,this->mask_var);
    doPacking(b,this->advertise_var);
}

void OFP_Port_Mod::parsimUnpack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimUnpack(b);
    doUnpacking(b,this->port_no_var);
    doUnpacking(b,this->hw_addr_var,6);
    doUnpacking(b,this->config_var);
    doUnpacking(b,this->mask_var);
    doUnpacking(b,this->advertise_var);
}

uint32_t OFP_Port_Mod::getPort_no() const
{
    return port_no_var;
}

void OFP_Port_Mod::setPort_no(uint32_t port_no)
{
    this->port_no_var = port_no;
}

unsigned int OFP_Port_Mod::getHw_addrArraySize() const
{
    return 6;
}

uint8_t OFP_Port_Mod::getHw_addr(unsigned int k) const
{
    if (k>=6) throw cRuntimeError("Array of size 6 indexed by %lu", (unsigned long)k);
    return hw_addr_var[k];
}

void OFP_Port_Mod::setHw_addr(unsigned int k, uint8_t hw_addr)
{
    if (k>=6) throw cRuntimeError("Array of size 6 indexed by %lu", (unsigned long)k);
    this->hw_addr_var[k] = hw_addr;
}

uint32_t OFP_Port_Mod::getConfig() const
{
    return config_var;
}

void OFP_Port_Mod::setConfig(uint32_t config)
{
    this->config_var = config;
}

uint32_t OFP_Port_Mod::getMask() const
{
    return mask_var;
}

void OFP_Port_Mod::setMask(uint32_t mask)
{
    this->mask_var = mask;
}

uint32_t OFP_Port_Mod::getAdvertise() const
{
    return advertise_var;
}

void OFP_Port_Mod::setAdvertise(uint32_t advertise)
{
    this->advertise_var = advertise;
}

class OFP_Port_ModDescriptor : public cClassDescriptor
{
  public:
    OFP_Port_ModDescriptor();
    virtual ~OFP_Port_ModDescriptor();

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

Register_ClassDescriptor(OFP_Port_ModDescriptor);

OFP_Port_ModDescriptor::OFP_Port_ModDescriptor() : cClassDescriptor("OFP_Port_Mod", "Open_Flow_Message")
{
}

OFP_Port_ModDescriptor::~OFP_Port_ModDescriptor()
{
}

bool OFP_Port_ModDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OFP_Port_Mod *>(obj)!=NULL;
}

const char *OFP_Port_ModDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OFP_Port_ModDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int OFP_Port_ModDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *OFP_Port_ModDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "port_no",
        "hw_addr",
        "config",
        "mask",
        "advertise",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int OFP_Port_ModDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "port_no")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hw_addr")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "config")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "mask")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "advertise")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OFP_Port_ModDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",
        "uint8_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *OFP_Port_ModDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OFP_Port_ModDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Port_Mod *pp = (OFP_Port_Mod *)object; (void)pp;
    switch (field) {
        case 1: return 6;
        default: return 0;
    }
}

std::string OFP_Port_ModDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Port_Mod *pp = (OFP_Port_Mod *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPort_no());
        case 1: return ulong2string(pp->getHw_addr(i));
        case 2: return ulong2string(pp->getConfig());
        case 3: return ulong2string(pp->getMask());
        case 4: return ulong2string(pp->getAdvertise());
        default: return "";
    }
}

bool OFP_Port_ModDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Port_Mod *pp = (OFP_Port_Mod *)object; (void)pp;
    switch (field) {
        case 0: pp->setPort_no(string2ulong(value)); return true;
        case 1: pp->setHw_addr(i,string2ulong(value)); return true;
        case 2: pp->setConfig(string2ulong(value)); return true;
        case 3: pp->setMask(string2ulong(value)); return true;
        case 4: pp->setAdvertise(string2ulong(value)); return true;
        default: return false;
    }
}

const char *OFP_Port_ModDescriptor::getFieldStructName(void *object, int field) const
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

void *OFP_Port_ModDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Port_Mod *pp = (OFP_Port_Mod *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


