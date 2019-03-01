/*
名稱：
        valid_socket - 保護 socket 外部函式 (efunctions)。
語法：
        int valid_socket( object caller, string function, mixed array info );

        整數 valid_socket( 物件 呼叫者, 字串 函式, 混合 陣列 資訊 );
用法：
        每一個 socket 外部函式執行之前，會先呼叫 valid_socket()。如果
        valid_socket() 傳回 0，則此 socket 外部函式失敗。反之，傳回 1 則成
        功。第一個參數 caller 是呼叫此 socket 外部函式的物件。第二個參數
        function 是被呼叫的 socket 外部函式名稱〈例如 socket_write() 或
        socket_bind()〉。第三個參數是一個資訊的陣列。如果有資訊的話，這個
        陣列的第一個元素 (element) 是被參考的檔案敍述值 (file descriptor
        being referenced)。第二個元素是擁有此 socket 的物件〈物件型態〉。
        第三個元素是此 socket 的遠端位址 (address of the remote end)〈字串
        型態〉。第四個元素是與 socket 相關的 (associated) 連接埠號碼 (port
        number)。
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版
*/

// valid_socket: controls access to socket efunctions
int valid_socket(object eff_user, string fun, mixed *info)
{
        return 1;
}

/*
int valid_socket(object caller, string func, mixed *info)
{
        // caller 在 login_ob 裏可能不會傳入物件
        if( !objectp(caller) )
                return 0;

        return is_daemon(caller) || is_command(caller) || caller->is_login_ob();
}
*/