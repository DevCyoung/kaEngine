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
    static void WriteLine(string str)
    {
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
        SCRIPT_ENUM_TYPE_NAME   = args[0]; //"eScriptType"; enum Name
        PATH_CONTENT_DIRECTION  = args[1]; //@"C:\Users\tkdlq\Desktop\assort\DirectX2D_Engine\Project\Content\";
        PATH_ENUM_SCRIPT_H      = args[2]; //@$"{PATH_CONTENT_DIRECTION}EnumScript.h";
        PATH_ENUM_SCRIPT_CPP    = args[3]; //@$"{PATH_CONTENT_DIRECTION}EnumScript.cpp";
                                           //
        //enum To String Function Name
        const string ENUM_TO_STRING_FUNCTION_NAME = "GetComponentWstrByEnum";
        const string RETURN_VALUE = "const wchar_t*";
        const string COMPONENT_NAMES = "ComponentNames";
        const string CONST = "const";
        const string REGISTER_SCRIPT_TYPE = "REGISTER_SCRIPT_TYPE";

        //get all .cppfile path

        List<string> scriptClassNames = new List<string>();

        string[] cppFilePths = Directory.GetFiles(PATH_CONTENT_DIRECTION, "*.h", System.IO.SearchOption.AllDirectories);
        foreach (string cppPath in cppFilePths)
        {
            StreamReader scriptCppWirter = new StreamReader(new FileStream(cppPath, FileMode.Open), Encoding.UTF8);

            if (null == scriptCppWirter)
            {
                WriteErrorLine("enumCppWirter is null");
                return;
            }

            string scriptCpp = scriptCppWirter.ReadToEnd();
            string className = Path.GetFileNameWithoutExtension(cppPath);
            scriptCpp = scriptCpp.Replace("\t", " ").Replace("\n", " ").Replace("\r", " ").Replace(" ", "");

            string scirptForamt = $"{REGISTER_SCRIPT_TYPE}({className})";

            if (scriptCpp.Contains(scirptForamt))
            {
                scriptClassNames.Add(className);
            }

            scriptCppWirter.Close();
        }

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
        enumHWirter.WriteLine(enumH);
        enumHWirter.Close();

        StreamWriter enumCppWirter = new StreamWriter(new FileStream(PATH_ENUM_SCRIPT_CPP, FileMode.Create), Encoding.UTF8);
        if (null == enumHWirter)
        {
            WriteErrorLine("enumCppWirter is null");
            return;
        }
        
        string enumCpp = "";
        enumCpp +=  "#include \"pch.h\"\n";
        enumCpp += $"#include \"{Path.GetFileName(PATH_ENUM_SCRIPT_H)}\"\n\n";
        //const wchar_t* eResAnimationPath[static_cast<UINT>(eResAnimation::End)]

        enumCpp += $"{RETURN_VALUE} {COMPONENT_NAMES}[static_cast<UINT>({SCRIPT_ENUM_TYPE_NAME}::End)]\n";
        enumCpp += "{\n";

        foreach (string item in scriptClassNames)
        {
            enumCpp += $"\tL\"{item}\",\n";
        }

        enumCpp += "};\n\n";

        enumCpp += $"{RETURN_VALUE} {ENUM_TO_STRING_FUNCTION_NAME}({CONST} {SCRIPT_ENUM_TYPE_NAME} type)\n";
        enumCpp += "{\n";
        enumCpp += $"\treturn {COMPONENT_NAMES}[static_cast<UINT>(type)];\n";
        enumCpp += "}\n";
        
        enumCppWirter.WriteLine(enumCpp);
        enumCppWirter.Close();
    }
}
