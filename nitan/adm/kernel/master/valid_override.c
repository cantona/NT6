// This program is a part of NT MudLIB

/*
名稱：
        valid_override - 控制 efun:: 的用途。
語法：
        int valid_override( string file, string efun_name, string mainfile );

        整數 valid_override( 字串 檔案, 字串 外部函式名, 字串 主檔案 );
用法：
        file 是該呼叫實際上所處的檔案；mainfile 是欲編譯的檔案〈因為
        #include 的關係，兩者可能會不同〉。

        在主宰物件 (master.c) 中加上 valid_override() 可以控制 efun:: 這種
        前置語法 (prefix) 的用途。每次當驅動程式嘗試編譯前面加上 efun:: 的
        函式時，會呼叫主宰物件中的 valid_override()。如果 valid_override()
        傳回 0，則編譯失敗。所以一些禁止由 efun:: 前置語法規避原作用的外部
        函式，valid_override() 可以提供一個方法修改它們的作用。

        如果您希望使用原來 3.1.2  版 efun:: 的作用，只需要在主宰物件
        master.c 中加上下面這行：

        int valid_override(string file, string efun) { return 1; }

        底下是一個限制較多的 valid_override() 範例：
        〈譯按：本範例與 21 版並無不同，但是目前已多了 mainfile 參數〉

        int valid_override( string file, string name )
        {
                if (file == "/adm/kernel/simul_efun") {
                        return 1;
                }

                if (name == "destruct")
                        return 0;
                if (name == "shutdown")
                        return 0;
                if (name == "snoop")
                        return 0;
                if (name == "exec")
                        return 0;

                return 1;
        }
參考：
        valid_object, function_exists
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版

*/
// valid_override: controls which simul_efuns may be overridden with
// efun:: prefix and which may not.  This function is only called at
// object compile-time
int valid_override( string file, string name )
{
        // simul_efun can override any simul_efun by Annihilator
        if( file == SIMUL_EFUN_OB || file == MASTER_OB )
                return 1;

        // Must use the move() defined in F_MOVE.
        if( (name == "move_object") && file != F_MOVE && file != F_COMMAND )
                return 0;

        if( (name == "destruct") && ! sscanf(file, "/adm/kernel/simul_efun/%s", file) )
                return 0;

        //  may also wish to protect destruct, shutdown, snoop, and exec.
        return 1;
}

/*
int valid_override(string file, string name, string mainfile)
{

        if( file[0..24] == SIMUL_EFUN_OB[0..24] ) return 1;

        switch(name)
        {
                case "memory_summary":
                case "destruct"        :
                case "shutdown"        :
                case "exec"        :        return 0;
                default                :        return 1;
        }
}
*/
