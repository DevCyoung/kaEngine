using System.Runtime.CompilerServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Transactions;

//EX) enum class eScriptType
//enum class eScriptType
//{
//    SampleScript,
//	  CameraScript,
//	  OhterCameraScript,	
//	  End,
//};

//EX) enum class eScriptType
//#include <Engine/ComponentTrait.h>
//#include "EnumScript.h"
//
//REGISTER_SCRIPT_TYPE(SampleScript);
//REGISTER_SCRIPT_TYPE(CameraScript);
//REGISTER_SCRIPT_TYPE(OhterCameraScript);


public class MyProgram
{
    //EnumScript.h
    static string? PATH_CONTENT_DIRECTION = null;
    static string? PATH_ENUM_SCRIPT_H = null; // target
    static string? PATH_ENUM_SCRIPT_CPP = null; // target
    static string? SCRIPT_ENUM_TYPE_NAME = null;
    static string? CONST = null;
    static string? REGISTER_SCRIPT_TYPE = null;
    static string? IS_MESSAGE = null;
    static bool IS_MESSAGE_BOOL = false;
    static void WriteLine(string str)
    {
        if (IS_MESSAGE_BOOL)
            Console.WriteLine($"ScriptGen: {str}");
    }

    static void WriteWarningLine(string str)
    {

        Console.WriteLine($"ScriptGen: Warning: {str}");
    }

    static void WriteErrorLine(string str)
    {

        Console.WriteLine($"ScriptGen: Error: {str}");
    }



    public static void Main(string[] args)
    {
        //PATH_CONTENT_DIRECTION = args[0];
        //PATH_ENUM_SCRIPT_H = args[1];
        //PATH_ENUM_TYPE_PATH = args[2];

        //PATH_CONTENT_DIRECTION = args[0];
        //PATH_ENUM_SCRIPT_H = args[1];
        //PATH_ENUM_TYPE_PATH = args[2];
        //0 content Path
        SCRIPT_ENUM_TYPE_NAME = args[0]; //"eScriptType"; enum Name
        PATH_CONTENT_DIRECTION = args[1]; //@"C:\Users\tkdlq\Desktop\assort\DirectX2D_Engine\Project\Content\";
        PATH_ENUM_SCRIPT_H = args[2]; //@$"{PATH_CONTENT_DIRECTION}EnumScript.h";
        PATH_ENUM_SCRIPT_CPP = args[3]; //@$"{PATH_CONTENT_DIRECTION}EnumScript.cpp";
        IS_MESSAGE = args[4]; //true or false
        if (IS_MESSAGE == "TRUE")
        {
            IS_MESSAGE_BOOL = true;
        }
        //enum To String Function Name
        const string ENUM_TO_STRING_FUNCTION_NAME = "GetComponentName";
        const string RETURN_VALUE = "const wchar_t*";
        const string COMPONENT_NAMES = "ScriptComponentNames";
        const string CONST = "const";
        const string REGISTER_SCRIPT_TYPE = "REGISTER_SCRIPT_TYPE";

        const string DEPENDENCY_FILE_NAME = "dpend.diff";

        const string GET_SCIRPT_BY_ENUM = "CreateScriptByEnum";                
        const string GET_SCRIPT_DECLARE = "Script* CreateScriptByName(const std::wstring& scriptName)";

        //get all .cppfile path

        List<string> scriptClassNames = new List<string>();

        //Check Script Files
        string[] cppFilePths = Directory.GetFiles(PATH_CONTENT_DIRECTION, "*.h", System.IO.SearchOption.AllDirectories);
        foreach (string cppPath in cppFilePths)
        {
            StreamReader scriptCppReader = new StreamReader(new FileStream(cppPath, FileMode.Open), Encoding.UTF8);

            if (null == scriptCppReader)
            {
                WriteErrorLine("scriptCppReader is null");
                return;
            }
            string className = Path.GetFileNameWithoutExtension(cppPath);
            string scriptCpp = scriptCppReader.ReadToEnd();
            string scirptForamt = $"{REGISTER_SCRIPT_TYPE}({className})";


            StringBuilder sb = new StringBuilder(scriptCpp.Length);
            foreach (char c in scriptCpp)
            {
                if (!char.IsWhiteSpace(c))
                {
                    sb.Append(c);
                }
            }

            if (scriptCpp.Contains(scirptForamt))
            {
                scriptClassNames.Add(className);
            }

            scriptCppReader.Close();
        }




        //의존성 검사
        {
            string depentdPath = Path.Combine(PATH_CONTENT_DIRECTION, DEPENDENCY_FILE_NAME);
            WriteLine("check dependency");
            StreamReader depenWirter = new StreamReader(new FileStream(depentdPath, FileMode.OpenOrCreate), Encoding.UTF8);

            if (null != depentdPath)
            {
                //a
                string a = depenWirter.ReadToEnd().Replace("\r\n", "");
                //WriteLine($"############.diff\n{a}#################");

                string b = "";
                foreach (string item in scriptClassNames)
                {
                    b += item;
                }

                //WriteLine($"##############scriptClassNames\n {b}####################");

                if (a == b)
                {
                    WriteLine("OK! Not Execute ScriptGen Program End File No Change :)");
                    depenWirter.Close();
                    return;
                }
            }

            depenWirter.Close();
        }







        //Header
        {
            StreamWriter enumHWirter = new StreamWriter(new FileStream(PATH_ENUM_SCRIPT_H, FileMode.Create), Encoding.UTF8);
            if (null == enumHWirter)
            {
                WriteErrorLine("enumHWirter is null");
                return;
            }

            string enumH = "";
            enumH += "#pragma once\n\n";
            enumH += $"enum class {SCRIPT_ENUM_TYPE_NAME}\n";
            enumH += "{\n";

            foreach (string item in scriptClassNames)
            {
                enumH += $"\t{item},\n";
            }

            enumH += $"\tEnd\n";
            enumH += "};\n\n";
            enumH += $"{RETURN_VALUE} {ENUM_TO_STRING_FUNCTION_NAME}({CONST} {SCRIPT_ENUM_TYPE_NAME} type);\n";
            enumH += $"{GET_SCRIPT_DECLARE};\n";
            enumH += $"Script* {GET_SCIRPT_BY_ENUM}({CONST} {SCRIPT_ENUM_TYPE_NAME} type);\n";
            enumHWirter.WriteLine(enumH);
            enumHWirter.Close();
        }




        //enumCppWirter Open
        StreamWriter enumCppWirter = new StreamWriter(new FileStream(PATH_ENUM_SCRIPT_CPP, FileMode.Create), Encoding.UTF8);
        {

            if (null == enumCppWirter)
            {
                WriteErrorLine("enumCppWirter is null");
                return;
            }
            string enumCpp = "";
            enumCpp += "#include \"pch.h\"\n";
            enumCpp += $"#include \"{Path.GetFileName(PATH_ENUM_SCRIPT_H)}\"\n\n";

            //all script header
            foreach (string item in scriptClassNames)
            {
                enumCpp += $"#include \"{item}.h\"\n";
            }
            enumCpp += "\n";


            //const wchar_t* GetComponentName(const eScriptType type)
            enumCpp += $"static constexpr {RETURN_VALUE} const {COMPONENT_NAMES}[static_cast<UINT>({SCRIPT_ENUM_TYPE_NAME}::End)]\n";
            enumCpp += "{\n";
            foreach (string item in scriptClassNames)
            {
                enumCpp += $"\tL\"{item}\",\n";
            }
            enumCpp += "};\n\n";
            enumCpp += $"{RETURN_VALUE} {ENUM_TO_STRING_FUNCTION_NAME}({CONST} {SCRIPT_ENUM_TYPE_NAME} type)\n";
            enumCpp += "{\n";
            enumCpp += $"\tassert(static_cast<UINT>(type) < static_cast<UINT>({SCRIPT_ENUM_TYPE_NAME}::End));\n";
            enumCpp += $"\treturn {COMPONENT_NAMES}[static_cast<UINT>(type)];\n";
            enumCpp += "}\n";
            enumCppWirter.WriteLine(enumCpp);


            //Script* GetScriptByName(const std::wstring& scriptName)
            string GetComponentScript = "";
            GetComponentScript += $"{GET_SCRIPT_DECLARE}\n";
            GetComponentScript += "{\n";
            GetComponentScript += "\tScript* script = nullptr;\n\n";
            if (scriptClassNames.Count != 0)
            {
                GetComponentScript += $"\tif (L\"{scriptClassNames[0]}\" == scriptName)\n";
                GetComponentScript += $"\t\tscript = new {scriptClassNames[0]};\n";
            }
            for (int i = 1; i < scriptClassNames.Count; i++)
            {
                GetComponentScript += $"\telse if (L\"{scriptClassNames[i]}\" == scriptName)\n";
                GetComponentScript += $"\t\tscript = new {scriptClassNames[i]};\n";
            }
            GetComponentScript += "\tassert(false);\n";
            GetComponentScript += $"\treturn script;\n";
            GetComponentScript += "}\n";
            enumCppWirter.WriteLine(GetComponentScript);







            //GetComponentScript enum
            GetComponentScript = "";

            GetComponentScript += $"Script* {GET_SCIRPT_BY_ENUM}({CONST} {SCRIPT_ENUM_TYPE_NAME} type)\n";
            GetComponentScript += "{\n";
            GetComponentScript += "\tScript* script = nullptr;\n\n";
            GetComponentScript += "\tswitch (type)\n";
            GetComponentScript += "\t{\n";
            foreach (string item in scriptClassNames)
            {
                GetComponentScript += $"\tcase {SCRIPT_ENUM_TYPE_NAME}::{item}:\n";
                GetComponentScript += $"\t\tscript = new {item};\n";
                GetComponentScript += $"\t\tbreak;\n";
            }
            GetComponentScript += "\tdefault:\n";
            GetComponentScript += "\t\tassert(false);\n";
            GetComponentScript += "\t\tbreak;\n";
            GetComponentScript += "\t}\n";

            GetComponentScript += $"\treturn script;\n";
            GetComponentScript += "}\n";

            enumCppWirter.WriteLine(GetComponentScript);
        }
        enumCppWirter.Close();


        //의존성 파일 생성
        {
            string depentdPath = Path.Combine(PATH_CONTENT_DIRECTION, DEPENDENCY_FILE_NAME);
            StreamWriter depenWirter = new StreamWriter(new FileStream(depentdPath, FileMode.Create), Encoding.UTF8);
            if (null == depenWirter)
            {
                WriteErrorLine("depenWirter is null");
                return;
            }

            foreach (string s in scriptClassNames)
            {
                depenWirter.WriteLine(s);
            }
            depenWirter.Close();
        }

    }
}
