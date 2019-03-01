// zhuwu.c

inherit ROOM;

void create()
{
        set("short", "竹屋");
        set("long", @LONG
這是竹屋內部，裡面幾乎沒有什麼擺設，倒是有一盞古燈燃著，
映得旁邊的一尊泥佛的影子不住的晃動。整個屋子布置得極其樸素，
看來主人是能耐的清苦的人。
LONG );
        set("exits", ([
                "out" : __DIR__"zhuwu",
        ]));
        setup();
        (CLASS_D("ultra") + "/shenni")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("nanhai shenni", this_object())))
                return sort_string(msg, 64, 4);

        if (! ob->is_fighting())
                msg += "一青衫老尼盤腿而坐，任由面前古燈閃爍，對"
                       "你的來到視若無物。";
        else
                msg += "只見一人正在與" +
                       (ob->is_fighting(this_player()) ? "你" : "人") +
                       "激戰，層層氣浪震得竹屋搖搖欲墜。";

        return sort_string(msg, 64, 4);
}