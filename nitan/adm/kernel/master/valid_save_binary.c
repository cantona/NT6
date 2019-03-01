// This program is a part of NT MudLIB

/*
名稱：
        valid_save_binary - 控制一個物件是否可以儲存它已載入的程式。
語法：
        int valid_save_binary( string file );

        整數 valid_save_binary( 字串 file );
用法：
        只有啟動 BINARIES 時有效。

        驅動程式編譯時，如果定義了 ALWAYS_SAVE_BINARIES；或是一個物件中使
        用了 #pragma save_binary，就會以程式的檔案名稱作為參數呼叫
        valid_save_binary。如果 valid_save_binary 傳回 1，此程式會儲存到硬
        碟中以加快重新載入的時間。反之則不儲存，下次重新載入時會如同往常一
        樣重新編譯一次。
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_save_binary: controls whether an object can save a binary
//   image of itself to the specified "save binaries directory"
//   (see config file)
int valid_save_binary(string filename)
{
        return 1;
}