//
// Generated file, do not edit! Created by nedtool 4.6 from messages/OFP_Flow_Mod.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OFP_Flow_Mod_m.h"

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

Register_Class(OFP_Flow_Mod);

OFP_Flow_Mod::OFP_Flow_Mod(const char *name, int kind) : ::Open_Flow_Message(name,kind)
{
    this->cookie_var = 0;
    this->cookie_mask_var = 0;
    this->table_id_var = 0;
    this->command_var = 0;
    this->idle_timeout_var = 0;
    this->hard_timeout_var = 0;
    this->priority_var = 0;
    this->buffer_id_var = 0;
    this->out_port_var = 0;
    this->out_group_var = 0;
    this->flags_var = 0;
    for (unsigned int i=0; i<2; i++)
        this->pad_var[i] = 0;
    actions_arraysize = 0;
    this->actions_var = 0;
}

OFP_Flow_Mod::OFP_Flow_Mod(const OFP_Flow_Mod& other) : ::Open_Flow_Message(other)
{
    actions_arraysize = 0;
    this->actions_var = 0;
    copy(other);
}

OFP_Flow_Mod::~OFP_Flow_Mod()
{
    delete [] actions_var;
}

OFP_Flow_Mod& OFP_Flow_Mod::operator=(const OFP_Flow_Mod& other)
{
    if (this==&other) return *this;
    ::Open_Flow_Message::operator=(other);
    copy(other);
    return *this;
}

void OFP_Flow_Mod::copy(const OFP_Flow_Mod& other)
{
    this->cookie_var = other.cookie_var;
    this->cookie_mask_var = other.cookie_mask_var;
    this->table_id_var = other.table_id_var;
    this->command_var = other.command_var;
    this->idle_timeout_var = other.idle_timeout_var;
    this->hard_timeout_var = other.hard_timeout_var;
    this->priority_var = other.priority_var;
    this->buffer_id_var = other.buffer_id_var;
    this->out_port_var = other.out_port_var;
    this->out_group_var = other.out_group_var;
    this->flags_var = other.flags_var;
    for (unsigned int i=0; i<2; i++)
        this->pad_var[i] = other.pad_var[i];
    this->match_var = other.match_var;
    delete [] this->actions_var;
    this->actions_var = (other.actions_arraysize==0) ? NULL : new ofp_action_output[other.actions_arraysize];
    actions_arraysize = other.actions_arraysize;
    for (unsigned int i=0; i<actions_arraysize; i++)
        this->actions_var[i] = other.actions_var[i];
}

void OFP_Flow_Mod::parsimPack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimPack(b);
    doPacking(b,this->cookie_var);
    doPacking(b,this->cookie_mask_var);
    doPacking(b,this->table_id_var);
    doPacking(b,this->command_var);
    doPacking(b,this->idle_timeout_var);
    doPacking(b,this->hard_timeout_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->buffer_id_var);
    doPacking(b,this->out_port_var);
    doPacking(b,this->out_group_var);
    doPacking(b,this->flags_var);
    doPacking(b,this->pad_var,2);
    doPacking(b,this->match_var);
    b->pack(actions_arraysize);
    doPacking(b,this->actions_var,actions_arraysize);
}

void OFP_Flow_Mod::parsimUnpack(cCommBuffer *b)
{
    ::Open_Flow_Message::parsimUnpack(b);
    doUnpacking(b,this->cookie_var);
    doUnpacking(b,this->cookie_mask_var);
    doUnpacking(b,this->table_id_var);
    doUnpacking(b,this->command_var);
    doUnpacking(b,this->idle_timeout_var);
    doUnpacking(b,this->hard_timeout_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->buffer_id_var);
    doUnpacking(b,this->out_port_var);
    doUnpacking(b,this->out_group_var);
    doUnpacking(b,this->flags_var);
    doUnpacking(b,this->pad_var,2);
    doUnpacking(b,this->match_var);
    delete [] this->actions_var;
    b->unpack(actions_arraysize);
    if (actions_arraysize==0) {
        this->actions_var = 0;
    } else {
        this->actions_var = new ofp_action_output[actions_arraysize];
        doUnpacking(b,this->actions_var,actions_arraysize);
    }
}

uint64_t OFP_Flow_Mod::getCookie() const
{
    return cookie_var;
}

void OFP_Flow_Mod::setCookie(uint64_t cookie)
{
    this->cookie_var = cookie;
}

uint64_t OFP_Flow_Mod::getCookie_mask() const
{
    return cookie_mask_var;
}

void OFP_Flow_Mod::setCookie_mask(uint64_t cookie_mask)
{
    this->cookie_mask_var = cookie_mask;
}

uint8_t OFP_Flow_Mod::getTable_id() const
{
    return table_id_var;
}

void OFP_Flow_Mod::setTable_id(uint8_t table_id)
{
    this->table_id_var = table_id;
}

uint8_t OFP_Flow_Mod::getCommand() const
{
    return command_var;
}

void OFP_Flow_Mod::setCommand(uint8_t command)
{
    this->command_var = command;
}

uint16_t OFP_Flow_Mod::getIdle_timeout() const
{
    return idle_timeout_var;
}

void OFP_Flow_Mod::setIdle_timeout(uint16_t idle_timeout)
{
    this->idle_timeout_var = idle_timeout;
}

uint16_t OFP_Flow_Mod::getHard_timeout() const
{
    return hard_timeout_var;
}

void OFP_Flow_Mod::setHard_timeout(uint16_t hard_timeout)
{
    this->hard_timeout_var = hard_timeout;
}

uint16_t OFP_Flow_Mod::getPriority() const
{
    return priority_var;
}

void OFP_Flow_Mod::setPriority(uint16_t priority)
{
    this->priority_var = priority;
}

uint32_t OFP_Flow_Mod::getBuffer_id() const
{
    return buffer_id_var;
}

void OFP_Flow_Mod::setBuffer_id(uint32_t buffer_id)
{
    this->buffer_id_var = buffer_id;
}

uint32_t OFP_Flow_Mod::getOut_port() const
{
    return out_port_var;
}

void OFP_Flow_Mod::setOut_port(uint32_t out_port)
{
    this->out_port_var = out_port;
}

uint32_t OFP_Flow_Mod::getOut_group() const
{
    return out_group_var;
}

void OFP_Flow_Mod::setOut_group(uint32_t out_group)
{
    this->out_group_var = out_group;
}

uint16_t OFP_Flow_Mod::getFlags() const
{
    return flags_var;
}

void OFP_Flow_Mod::setFlags(uint16_t flags)
{
    this->flags_var = flags;
}

unsigned int OFP_Flow_Mod::getPadArraySize() const
{
    return 2;
}

uint8_t OFP_Flow_Mod::getPad(unsigned int k) const
{
    if (k>=2) throw cRuntimeError("Array of size 2 indexed by %lu", (unsigned long)k);
    return pad_var[k];
}

void OFP_Flow_Mod::setPad(unsigned int k, uint8_t pad)
{
    if (k>=2) throw cRuntimeError("Array of size 2 indexed by %lu", (unsigned long)k);
    this->pad_var[k] = pad;
}

oxm_basic_match& OFP_Flow_Mod::getMatch()
{
    return match_var;
}

void OFP_Flow_Mod::setMatch(const oxm_basic_match& match)
{
    this->match_var = match;
}

void OFP_Flow_Mod::setActionsArraySize(unsigned int size)
{
    ofp_action_output *actions_var2 = (size==0) ? NULL : new ofp_action_output[size];
    unsigned int sz = actions_arraysize < size ? actions_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        actions_var2[i] = this->actions_var[i];
    actions_arraysize = size;
    delete [] this->actions_var;
    this->actions_var = actions_var2;
}

unsigned int OFP_Flow_Mod::getActionsArraySize() const
{
    return actions_arraysize;
}

ofp_action_output& OFP_Flow_Mod::getActions(unsigned int k)
{
    if (k>=actions_arraysize) throw cRuntimeError("Array of size %d indexed by %d", actions_arraysize, k);
    return actions_var[k];
}

void OFP_Flow_Mod::setActions(unsigned int k, const ofp_action_output& actions)
{
    if (k>=actions_arraysize) throw cRuntimeError("Array of size %d indexed by %d", actions_arraysize, k);
    this->actions_var[k] = actions;
}

class OFP_Flow_ModDescriptor : public cClassDescriptor
{
  public:
    OFP_Flow_ModDescriptor();
    virtual ~OFP_Flow_ModDescriptor();

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

Register_ClassDescriptor(OFP_Flow_ModDescriptor);

OFP_Flow_ModDescriptor::OFP_Flow_ModDescriptor() : cClassDescriptor("OFP_Flow_Mod", "Open_Flow_Message")
{
}

OFP_Flow_ModDescriptor::~OFP_Flow_ModDescriptor()
{
}

bool OFP_Flow_ModDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OFP_Flow_Mod *>(obj)!=NULL;
}

const char *OFP_Flow_ModDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OFP_Flow_ModDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount(object) : 14;
}

unsigned int OFP_Flow_ModDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<14) ? fieldTypeFlags[field] : 0;
}

const char *OFP_Flow_ModDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "cookie",
        "cookie_mask",
        "table_id",
        "command",
        "idle_timeout",
        "hard_timeout",
        "priority",
        "buffer_id",
        "out_port",
        "out_group",
        "flags",
        "pad",
        "match",
        "actions",
    };
    return (field>=0 && field<14) ? fieldNames[field] : NULL;
}

int OFP_Flow_ModDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cookie")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cookie_mask")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "table_id")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "idle_timeout")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hard_timeout")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+6;
    if (fieldName[0]=='b' && strcmp(fieldName, "buffer_id")==0) return base+7;
    if (fieldName[0]=='o' && strcmp(fieldName, "out_port")==0) return base+8;
    if (fieldName[0]=='o' && strcmp(fieldName, "out_group")==0) return base+9;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+10;
    if (fieldName[0]=='p' && strcmp(fieldName, "pad")==0) return base+11;
    if (fieldName[0]=='m' && strcmp(fieldName, "match")==0) return base+12;
    if (fieldName[0]=='a' && strcmp(fieldName, "actions")==0) return base+13;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OFP_Flow_ModDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",
        "uint64_t",
        "uint8_t",
        "uint8_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint16_t",
        "uint8_t",
        "oxm_basic_match",
        "ofp_action_output",
    };
    return (field>=0 && field<14) ? fieldTypeStrings[field] : NULL;
}

const char *OFP_Flow_ModDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OFP_Flow_ModDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Flow_Mod *pp = (OFP_Flow_Mod *)object; (void)pp;
    switch (field) {
        case 11: return 2;
        case 13: return pp->getActionsArraySize();
        default: return 0;
    }
}

std::string OFP_Flow_ModDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Flow_Mod *pp = (OFP_Flow_Mod *)object; (void)pp;
    switch (field) {
        case 0: return uint642string(pp->getCookie());
        case 1: return uint642string(pp->getCookie_mask());
        case 2: return ulong2string(pp->getTable_id());
        case 3: return ulong2string(pp->getCommand());
        case 4: return ulong2string(pp->getIdle_timeout());
        case 5: return ulong2string(pp->getHard_timeout());
        case 6: return ulong2string(pp->getPriority());
        case 7: return ulong2string(pp->getBuffer_id());
        case 8: return ulong2string(pp->getOut_port());
        case 9: return ulong2string(pp->getOut_group());
        case 10: return ulong2string(pp->getFlags());
        case 11: return ulong2string(pp->getPad(i));
        case 12: {std::stringstream out; out << pp->getMatch(); return out.str();}
        case 13: {std::stringstream out; out << pp->getActions(i); return out.str();}
        default: return "";
    }
}

bool OFP_Flow_ModDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Flow_Mod *pp = (OFP_Flow_Mod *)object; (void)pp;
    switch (field) {
        case 0: pp->setCookie(string2uint64(value)); return true;
        case 1: pp->setCookie_mask(string2uint64(value)); return true;
        case 2: pp->setTable_id(string2ulong(value)); return true;
        case 3: pp->setCommand(string2ulong(value)); return true;
        case 4: pp->setIdle_timeout(string2ulong(value)); return true;
        case 5: pp->setHard_timeout(string2ulong(value)); return true;
        case 6: pp->setPriority(string2ulong(value)); return true;
        case 7: pp->setBuffer_id(string2ulong(value)); return true;
        case 8: pp->setOut_port(string2ulong(value)); return true;
        case 9: pp->setOut_group(string2ulong(value)); return true;
        case 10: pp->setFlags(string2ulong(value)); return true;
        case 11: pp->setPad(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *OFP_Flow_ModDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 12: return opp_typename(typeid(oxm_basic_match));
        case 13: return opp_typename(typeid(ofp_action_output));
        default: return NULL;
    };
}

void *OFP_Flow_ModDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OFP_Flow_Mod *pp = (OFP_Flow_Mod *)object; (void)pp;
    switch (field) {
        case 12: return (void *)(&pp->getMatch()); break;
        case 13: return (void *)(&pp->getActions(i)); break;
        default: return NULL;
    }
}


