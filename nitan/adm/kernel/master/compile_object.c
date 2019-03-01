// This program is a part of NT MudLIB

// compile_object: This is used for loading MudOS "virtual" objects.
// It should return the object the mudlib wishes to associate with the
// filename named by 'file'.  It should return 0 if no object is to be
// associated.
/*
名稱：
        compile_object - 提供虛擬物件 (virtual object) 功能的 mudlib 介面。
語法：
        object compile_object( string pathname );

        物件 compile_object( 字串 路徑名 );
用法：
        當 mudlib 指示驅動程式載入一個不存在于記憶體中的檔案，驅動程式會呼
        叫 compile_object 函式。舉例來說，如果 mudlib 呼叫
        call_other("/obj/file.r", "some_function") 或 new("/obj/file.r") 時
        ，記憶體中沒有叫做 /obj/file.r.c 的東西，驅動程式就呼叫主宰物件
         (master object) 的 compile_object("/obj/file.r")。如果 mudlib 不希
        望連結 (associate) /obj/file.r 檔案，compile_object() 將傳回 0。如
        果 mudlib 願意，就要傳回 /obj/file.r 這個物件。在 compile_object()
        連結一個檔案名稱和物件之後，對驅動程式而言，就如同遊戲中存在
        file.r.c 這個檔案，而載入此物件時產生的就是 compile_object() 傳回的
        物件。
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.20.    v22 版
*/

varargs mixed compile_object(string file, int cloning)
{
        object daemon;

        if( daemon = find_object(VIRTUAL_D) )
                return daemon->compile_object(file, cloning);
        else
                return 0;
}