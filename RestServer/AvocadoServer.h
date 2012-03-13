////////////////////////////////////////////////////////////////////////////////
/// @brief avocado server
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2011-2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_REST_SERVER_AVOCADO_SERVER_H
#define TRIAGENS_REST_SERVER_AVOCADO_SERVER_H 1

#include "Rest/AnyServer.h"

#include "Admin/ApplicationAdminServer.h"
#include "HttpServer/ApplicationHttpServer.h"
#include "VocBase/vocbase.h"
#include "VocBase/query-error.h"

// -----------------------------------------------------------------------------
// --SECTION--                                               class AvocadoServer
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup AvocadoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

namespace triagens {
  namespace avocado {

////////////////////////////////////////////////////////////////////////////////
/// @brief AvocadoDB server
////////////////////////////////////////////////////////////////////////////////

  class AvocadoServer : public rest::AnyServer {
      private:
        AvocadoServer (const AvocadoServer&);
        AvocadoServer& operator= (const AvocadoServer&);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup AvocadoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief UnviversalVoc constructor
////////////////////////////////////////////////////////////////////////////////

        AvocadoServer (int argc, char** argv);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 AnyServer methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup AvocadoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        void buildApplicationServer ();

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        int startupServer ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   private methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup AvocadoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief executes the shell
////////////////////////////////////////////////////////////////////////////////

        void executeShell ();

////////////////////////////////////////////////////////////////////////////////
/// @brief opens the database
////////////////////////////////////////////////////////////////////////////////

        void openDatabase ();

////////////////////////////////////////////////////////////////////////////////
/// @brief closes the database
////////////////////////////////////////////////////////////////////////////////

        void closeDatabase ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup AvocadoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief number of command line arguments
////////////////////////////////////////////////////////////////////////////////

        int _argc;

////////////////////////////////////////////////////////////////////////////////
/// @brief command line arguments
////////////////////////////////////////////////////////////////////////////////

        char** _argv;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to binary
////////////////////////////////////////////////////////////////////////////////

        std::string _binaryPath;

////////////////////////////////////////////////////////////////////////////////
/// @brief constructed admin server application
////////////////////////////////////////////////////////////////////////////////

        admin::ApplicationAdminServer* _applicationAdminServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief constructed http server application
////////////////////////////////////////////////////////////////////////////////

        rest::ApplicationHttpServer* _applicationHttpServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief constructed http server
////////////////////////////////////////////////////////////////////////////////

        rest::HttpServer* _httpServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief constructed admin http server
////////////////////////////////////////////////////////////////////////////////

        rest::HttpServer* _adminHttpServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief list port for client requests
///
/// @CMDOPT{--server.http-port @CA{port}}
///
/// Specifies the @CA{port} for HTTP requests by clients. This will bind to any
/// address available.
///
/// @CMDOPT{--server.http-port @CA{address}:@CA{port}}
///
/// Specifies the @CA{port} for HTTP requests by clients. This will bind to the
/// given @CA{address}, which can be a numeric value like @CODE{192.168.1.1} or
/// a name.
///
/// @CMDOPT{--port @CA{port}}
///
/// This variant can be used as command line option.
////////////////////////////////////////////////////////////////////////////////

        string _httpPort;

////////////////////////////////////////////////////////////////////////////////
/// @brief list port for admin requests
///
/// @CMDOPT{--server.admin-port @CA{port}}
///
/// Specifies the @CA{port} for HTTP requests by the administrator. This will
/// bind to any address available.
///
/// @CMDOPT{--server.admin-port @CA{address}:@CA{port}}
///
/// Specifies the @CA{port} for HTTP requests by the administrator. This will
/// bind to the given @CA{address}, which can be a numeric value like
/// 192.168.1.1 or a name.
////////////////////////////////////////////////////////////////////////////////

        string _adminPort;

////////////////////////////////////////////////////////////////////////////////
/// @brief number of dispatcher threads
////////////////////////////////////////////////////////////////////////////////

        int _dispatcherThreads;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to the directory containing alternate startup scripts
///
/// @CMDOPT{--startup.directory @CA{directory}}
///
/// Specifies the @CA{directory} path to alternate startup Javascript files.
/// Normally, the server will start using built-in Javascript core 
/// functionality. To override the core functionality with a different 
/// implementation, this option can be used.
////////////////////////////////////////////////////////////////////////////////

        string _startupPath;

////////////////////////////////////////////////////////////////////////////////
/// @brief semicolon separated list of module directories
///
/// @CMDOPT{--startup.modules-path @CA{directory}}
///
/// Specifies the @CA{directory} path with user defined Javascript modules.
/// Multiple paths can be specified separated with commas.
////////////////////////////////////////////////////////////////////////////////

        string _startupModules;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to the action directory
///
/// @CMDOPT{--action.directory @CA{directory}}
///
/// Specifies the @CA{directory} path to user defined Javascript files that
/// can be invoked as actions.
////////////////////////////////////////////////////////////////////////////////

        string _actionPath;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to the system action directory
///
/// @CMDOPT{--action.system-directory @CA{directory}}
///
/// Specifies the @CA{system-directory} path to system defined Javascript files 
/// that can be invoked as actions.
////////////////////////////////////////////////////////////////////////////////

        string _systemActionPath;

////////////////////////////////////////////////////////////////////////////////
/// @brief number of action threads
///
/// @CMDOPT{--action.threads @CA{number}}
///
/// Specifies the @CA{number} of threads that are spawned to handle action 
/// requests.
////////////////////////////////////////////////////////////////////////////////

        int _actionThreads;

////////////////////////////////////////////////////////////////////////////////
/// @brief Javascript garbage collection interval (each x requests)
///
/// @CMDOPT{--gc.interval @CA{interval}}
///
/// Specifies the interval (approximately in number of requests) that the 
/// garbage collection for Javascript objects will be run in each thread.
////////////////////////////////////////////////////////////////////////////////

        uint64_t _gcInterval;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to the database
///
/// @CMDOPT{--database.directory @CA{directory}}
///
/// The directory containing the collections and data-files. Defaults
/// to @CODE{/var/lib/avocado}.
///
/// @CMDOPT{@CA{directory}}
///
/// When using the command line version, you can simply supply the database
/// directory as argument.
///
/// @verbinclude start2
////////////////////////////////////////////////////////////////////////////////

        string _databasePath;

////////////////////////////////////////////////////////////////////////////////
/// @brief vocbase
////////////////////////////////////////////////////////////////////////////////

        TRI_vocbase_t* _vocbase;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:
