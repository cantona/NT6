// This program is a part of NT MudLIB

mixed valid_database(object ob, string action, mixed *info)
{
        if( !objectp(ob) || (geteuid(ob) != ROOT_UID) )
                return 0;

        else
        {
                if( action == "connect" ) {
                        /*
                         * 這裡演示的多站點數據庫互動
                         * 協作的返回密碼寫法，單站點
                         * 簡單返回密碼即可（by Find）
                         */
                        switch (info[1])
                        {
                                case "222.186.34.42":
                                        return "nt150867";      // 這個站點的密碼
                                case "127.0.0.1":
                                case "localhost":
                                        return "nt150867";      // 本地站點的密碼
                                default:
                                        return 0;
                        }

                }
                else
                        return 1;
        }
}
