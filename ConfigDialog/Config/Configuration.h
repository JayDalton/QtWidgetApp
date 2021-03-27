#pragma once

#include "Parameter.h"

/////////////////////////////////////////////////////////////////////////////

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   //bool loadJsonFile(const fs::path& filePath);
   //bool saveJsonFile(const fs::path& filePath) const;

protected:
   void registerBaseParameter(const BaseParameter& parameter);
   void registerListParameter(const ListParameter& parameter);

   const ParameterVariant& getParameter(const std::string& ident) const;
   const BaseParameter& getBaseParameter(const std::string& ident) const;
   const ListParameter& getListParameter(const std::string& ident) const;

   bool setParameter(const std::string& ident, BaseValue value);
   bool setParameter(const std::string& ident, const std::string& value);

   const std::string& getStringParameter(const std::string& ident) const;
   const fs::path& getPathParameter(const std::string& ident) const;

private:
   ParameterMapping m_paramMap;
};

///////////////////////////////////////////////////////////////////////////

struct ApplicationConfig : public Configuration
{
   ApplicationConfig();

   std::string getDefaultImportMatrix() const;
   void setDefaultImportMatrix(const std::string& file);

   std::string getDefaultMatrixFolder() const;
   void setDefaultMatrixFolder(std::string_view file);

   std::vector<std::string> getFolderFilelist() const;
   void setFolderFilelist(const std::vector<std::string>& list);

private:
   static constexpr const char* DEFAULT_MATRIX_IMPORT{"matrixImport"};
   static constexpr const char* DEFAULT_MATRIX_FOLDER{"matrixFolder"};
   static constexpr const char* DEFAULT_LOGFILE_FOLDER{"loggingFolder"};
   static constexpr const char* MATRIX_FOLDER_FILELIST{"folderFileFist"};
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
