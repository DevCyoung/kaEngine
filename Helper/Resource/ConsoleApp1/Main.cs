using System.Text;

public class MyProgram
{
    static string PRAGMA_ONCE = "#pragma once\n\n";
    static string SHARP_INCLUDE = "#include";    
    static string BEGIN_ENGINE_NAMESPACE = "namespace engine\n{\n";
    static string END_ENGINE_NAMESPACE = "}//namespace engine End";
    static string RESOURCE_PATH = "";

    static void WriteLine(string str)
    {
        Console.WriteLine($"EnumResource: {str}");
    }

    static void WriteWarningLine(string str)
    {
        Console.WriteLine($"EnumResource: Warning: {str}");
    }

    static void WriteErrorLine(string str)
    {
        Console.WriteLine($"EnumResource: Error: {str}");
    }

    public static void Main(string[] args)
    {
        
        if (args.Length == 2)
        {
            WriteLine("Program Ready.....");
            WriteLine("Input Check....");
            WriteLine($"argc = {args.Length}");
            WriteLine("args length is 2, ok! Program start");

            WriteLine("###########Input Path############");
            foreach (string arg in args)
            {
                WriteLine($"arg = {arg}");
            }
            WriteLine("###########Input Path############");            

            string path = @"";
            string targetPath = @"";

            path += args[0];
            targetPath += args[1];

            RESOURCE_PATH = path;

            if (targetPath[targetPath.Length - 1] != '\\')
            {
                targetPath += '\\';
            }

            string resourcePath = path;

            string[] resourceDirectorys = Directory.GetDirectories(resourcePath);

            if (null == resourceDirectorys)
            {
                WriteErrorLine($"resourceDirectorys is null has directory? path({resourcePath})");
                return;
            }

            WriteLine("###########Create Files############");
            foreach (string resDirectory in resourceDirectorys)
            {
                string enumType = GetFileName(resDirectory);


                List<string> enumNames = new List<string>();
                List<string> enumFilePath = new List<string>();

                MakeEnumNames(resDirectory, enumNames, enumFilePath, "");

                string enumHeader = MakeEnumNumHeader(enumType, enumNames);

                string enumHeaderPath =
                   targetPath + "EnumResourceType" + enumType + ".h";

                StreamWriter enumHearderWriter = new StreamWriter(
                new FileStream(enumHeaderPath
                , FileMode.Create)
                , Encoding.UTF8);


                if (null == enumHearderWriter)
                {
                    WriteErrorLine($"enumHearderWriter, check your enumHeaderPath... enumHeaderPath(Create fullPath) = " +
                        $"{enumHeaderPath} targetPath = {targetPath}");
                    return;
                }
                else
                {
                    enumHearderWriter.WriteLine(enumHeader);                    
                    enumHearderWriter.Close();
                    WriteLine($"CreateHeaderFile = {enumHeaderPath}");
                }              

                string enumCpp = MakeEnumCpp(enumType, enumFilePath);

                string enumCppPath =
                    targetPath + "EnumResourceType" + enumType + ".cpp";

                StreamWriter enumCppWirter = new StreamWriter(
                new FileStream(enumCppPath
                , FileMode.Create)
                , Encoding.UTF8);

                if (null == enumCppWirter)
                {
                    WriteErrorLine($"enumCppWirter, check your enumCppPath... enumCppPath(Create fullPath) = " +
                        $"{enumCppPath} targetPath = {targetPath}");                    
                }
                else
                {
                    enumCppWirter.WriteLine(enumCpp);                    
                    enumCppWirter.Close();
                    WriteLine($"CreateCppFile = {enumCppPath}");
                }                
            }


            WriteLine("###########Create Files############");
            WriteLine("Success End...");
        }
        else
        {
            if (args.Length == 3)
            {
                if (args[2] == "NO")
                {
                    WriteLine("OK! Not Execute Enum Program End");
                }
                else
                {
                    WriteErrorLine($"Check third argument... Please change \"{args[2]}\" -> \"NO\" and,  program not execute");
                }
            }
            else
            {
                WriteErrorLine("need 2 arguments, No Execute Enum Program End");
            }            
        }

    }

    public static string[] GetDirectories(string resourcePath)
    {
        string[] directorys = Directory.GetDirectories(resourcePath);

        foreach (string directory in directorys)
        {
            GetDirectories(directory);
        }

        string[] fileNames = Directory.GetFiles(resourcePath);

        return directorys;
    }

    public static string GetFileName(string path)
    {
        string[] split = path.Split('\\');
        string fileName = split[split.Length - 1];

        return fileName;
    }

    public static void MakeEnumNames(string resDirectory,
        List<string> enumNames,
        List<string> enumFilePath,
        string recursiveEnumName)
    {
        string[] directorys = Directory.GetDirectories(resDirectory);

        foreach (string directory in directorys)
        {
            string prev = recursiveEnumName;

            recursiveEnumName += GetFileName(directory) + "_";
            MakeEnumNames(directory, enumNames, enumFilePath, recursiveEnumName);

            recursiveEnumName = prev;
        }

        string[] fileNames = Directory.GetFiles(resDirectory);




        foreach (string fileName in fileNames)
        {
            string perfactEnumName = recursiveEnumName + Path.GetFileNameWithoutExtension(
                GetFileName(fileName));
            enumNames.Add(perfactEnumName);

            string resourceBaseFileName = fileName.Replace(resDirectory, "");
            resourceBaseFileName = resourceBaseFileName.Replace("\\", "\\\\");
            enumFilePath.Add(fileName.Replace(RESOURCE_PATH, "").Replace("\\", "\\\\"));

        }
    }


    public static string MakeEnumNumHeader(string enumType, List<string> enumNames)
    {
        string header = "";

        header += PRAGMA_ONCE;

        header += BEGIN_ENGINE_NAMESPACE;
        {
            header += "\tenum class " + "eRes" + enumType + "\n";
            header += "\t{\n";

            foreach (string enumName in enumNames)
            {
                header += "\t\t" + enumName + ",\n";
            }
            header += "\t" + "\tEnd\n";
            header += "\t};\n\n";

            if (enumNames.Count > 0)
            {
                header += $"\tconst wchar_t* EnumResourcePath(eRes{enumType} type);\n";
            }

        }
        header += END_ENGINE_NAMESPACE;

        return header;
    }

    //enum to Path
    public static string MakeEnumCpp(string enumType, List<string> relativePaths)
    {
        string cpp = "";
        string eResEnumType = $"eRes{enumType}";
        string enumResourcePathArray = $"{eResEnumType}Path";


        cpp += $"{SHARP_INCLUDE} \"pch.h\"\n";
        cpp += $"{SHARP_INCLUDE} \"EnumResourceType{enumType}.h\"\n\n";

        cpp += BEGIN_ENGINE_NAMESPACE;
        {
            //const wchar
            if (relativePaths.Count > 0)
            {
                cpp += $"\tconst wchar_t* {enumResourcePathArray}[static_cast<UINT>({eResEnumType}::End)]\n";
                cpp += "\t{\n";

                foreach (string relativePath in relativePaths)
                {
                    //리소스 하위로가져온다.
                    cpp += $"\t\tL\"{relativePath}\",\n";
                }
                cpp += "\t};\n";
                cpp += "\n";
                cpp += $"\tconst wchar_t* EnumResourcePath(eRes{enumType} type)\n";
                cpp += "\t{\n";
                cpp += $"\t\treturn {enumResourcePathArray}[static_cast<UINT>(type)];\n";
                cpp += "\t}\n";
            }
        }
        cpp += END_ENGINE_NAMESPACE;

        return cpp;
    }



}