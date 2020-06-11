#pragma once

class WUtils
{
public:

    static std::string GetCurDir()
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        auto p = converter.to_bytes( fs::current_path() );
        std::replace( p.begin(), p.end(), '\\', '/' );

        return std::string(p);

    } // GetCurDir

    static std::wstring GetCurDirFullW( const char* postfix )
    {
        std::string  path_html_main  = WUtils::GetCurDir() + "/WInformer/Main.html";
        std::wstring wpath_html_main = std::wstring(L"file://") + fs::canonical( path_html_main ).c_str();

        return wpath_html_main;

    } // GetCurDir

    //#pragma warning(disable : 4996)
    template<typename ... Args> static std::string string_format( const char* format, Args ... args )
    {
        size_t size = snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
        unique_ptr<char[]> buf( new char[ size ] );
        snprintf( buf.get(), size, format, args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }

}; // class WUtils
