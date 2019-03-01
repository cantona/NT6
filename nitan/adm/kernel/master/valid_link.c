// This program is a part of NT MudLIB

/*
名稱：
        valid_link - 控制 link 外部函式的用途。
語法：
        int valid_link( string from, string to );

        整數 valid_link( 字串 from, 字串 to );
用法：
        驅動程式回從 link(from, to) 外部函式裡面呼叫主宰物件 (master
        object) 裡面的 valid_link(from, to) 函式。如果 valid_link() 傳回 0
        ，則 link() 的動作失敗。如果傳回 1，還需要以同樣的參數呼叫
        rename() 成功。
參考：
        link
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版

*/

// valid_link: controls use of the link() efun for creating hard links between paths
int valid_link(string original, string reference)
{
        return 0;
}