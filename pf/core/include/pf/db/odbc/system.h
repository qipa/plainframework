/**
 * PLAIN FRAMEWORK ( https://github.com/viticm/plainframework )
 * $Id system.h
 * @link https://github.com/viticm/plainframework for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.it@gmail.com>
 * @date 2014/06/23 10:34
 * @uses the db system class, to provide some convenient operation functions.
 */
#ifndef PF_DB_ODBC_SYSTEM_H_
#define PF_DB_ODBC_SYSTEM_H_

#ifdef PF_OPEN_ODBC

#include "pf/db/odbc/config.h"
#include "pf/basic/tinytimer.h"

namespace pf_db {

namespace odbc {

class PF_API System {
 public:
   enum dboption_type_t {
     kDBOptionTypeLoad,
     kDBOptionTypeSave, //insert and update
     kDBOptionTypeAddNew,
     kDBOptionTypeDelete,
     kDBOptionTypeQuery,
     kDBOptionTypeInitEmpty, //db at init state
   };
#if OS_WIN
   enum odbc_error_t {
     kODBCErrorSamePrimaryKey = 2601, //repeat primary key
   };
#elif OS_UNIX
   enum odbc_error_t {
     kODBCErrorSamePrimaryKey = 1026, //repeat primary key
   };
#endif

 public:
   System();
   virtual ~System();

 public:
   bool init(const char *connectionname,
             const char *username,
             const char *password);

 public:
   uint32_t get_result_count();
   int get_error_code();
   const char *get_error_message();
   virtual bool add_new(const std::string &sql_str);
   virtual bool _delete(const std::string &sql_str);
   virtual bool save(const std::string &sql_str);
   int32_t get_columncount() const;
   bool getresult() const;
   virtual bool query(const std::string &sql_str);
   bool fetch(int32_t orientation = 1, int32_t offset = 0);
   bool check_db_connect(); //check the connect if work, 
                            //and repeat 5 times when fails
   Interface *getinterface();
   db_columntype_t gettype(int32_t column_index);


 protected:
   int32_t result_count_;
   bool result_;
   dboption_type_t op_type_;
   Interface *odbc_interface_;
   pf_basic::TinyTimer timer_;

 protected:
   int32_t get_internal_affect_count();
   bool is_prepare();
   bool long_load();
   bool long_save();
};

}; //namespace odbc

}; //namespace pf_db

#endif //PF_OPEN_ODBC

#endif //PF_DB_ODBC_SYSTEM_H_
