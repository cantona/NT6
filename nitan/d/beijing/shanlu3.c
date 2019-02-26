inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是山中的一片叢林，灌木中夾雜着一些野花，被高大的樹木
遮住了陽光。一塊巨大的石頭倚樹而卧。
LONG );
        set("exits", ([
                "eastdown" : "/d/beijing/shanlu2",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 30);
	setup();
        (CLASS_D("ultra") + "/kuihua")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("kuihua taijian", this_object())))
                return sort_string(msg, 70, 4);

        if (! ob->is_fighting())
                msg += "有一個黃衫人靠在石上，痴痴的望着遠方，一動不動"
                       "的，也不知道他在這裏究竟待了多久。";
        else
                msg += "只見一黃衫人身形詭祕，進退疾若閃電，正在與" +
                       (ob->is_fighting(this_player()) ? "你" : "人") +
                       "激戰。";

        return sort_string(msg, 70, 4);
}