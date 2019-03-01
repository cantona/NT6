// This program is a part of NT MudLIB

/*
名稱：
        valid_object - 讓你能控制是否要載入某個物件。
語法：
        int valid_object( object obj );

        整數 valid_object( 物件 物件 );
用法：
        載入一個物件之後，驅動程式會以新創造的物件為參數，呼叫主宰物件
        (master object) 的 valid_object()。如果 valid_object() 存在，並傳
        回 0，則會摧毀此物件並使載入物件的外部函式 (efun) 產生錯誤輸出。如
        果此函式不存在或是傳回 1，則載入物件的過程就跟平常一樣。此函式呼叫
        時，該物件還沒有機會執行任何程式碼，包括 create()在內，所以該物件
        除了 file_name(obj) 之外，沒有多少東西有效。
參考：
        valid_override
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版
*/
// valid_object: controls whether an object loaded by the driver should exist
int valid_object(object ob)
{
        return (!clonep(ob)) || inherits(F_MOVE, ob);
}