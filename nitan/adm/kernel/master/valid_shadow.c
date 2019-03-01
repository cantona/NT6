// This program is a part of NT MudLIB

/*

        valid_shadow - 控制哪些物件可以被投影 (shadow)。
語法：
        int valid_shadow( object ob );

        整數 valid_shadow( 物件 物件 );
用法：
        當一個物件嘗試投影 ob 時〈使用 shadow() 外部函式 (efun)〉，會呼叫
        主宰物件中的 valid_shadow() 函式。一個物件應該作為此函式的參數。此
        物件是 previous_object() 嘗試投影的物件。如果不準投影，
        valid_shadow() 應傳回 0，導致 shadow() 呼叫失敗並傳回 0。如果
        valid_shadow() 傳回 1，則允許投影。
參考：
        shadow, query_shadowing
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_shadow: controls whether an object may be shadowed or not
int valid_shadow(object ob)
{
        object pre;

        pre = previous_object();
        if( geteuid(pre) == ROOT_UID ||
            sscanf(file_name(pre), "/shadow/%*s") ) {
                return 1;
        }

        log_file("shadow", sprintf("%O try to shadow %O failed.\n", pre, ob));
        return 0;
}
