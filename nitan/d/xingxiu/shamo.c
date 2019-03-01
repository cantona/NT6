// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
       set("short","大沙漠");
        set("long", @LONG
這是一片一望無際的大沙漠。你一進來就迷失了方向。看來要走
出這塊沙漠並非易事。
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));

        set("outdoors", "xiyu");
        set("no_map", "這裡的地形令人困惑，你無從下手繪制地圖。\n");

        setup();
}

int valid_leave(object me, string dir)
{
        int water, food;
        int qi, jing;
        string dest;

        if (playerp(me))
        {
                if( !objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
                {
                water=query("water", me);
                food=query("food", me);
                water -= (random(2) + 1) * water / 20 + 5;
                food -= (random(2) + 1) * food / 20 + 5;
                if (water < 0) water = 0;
                if (food < 0) food = 0;
                set("water", water, me);
                set("food", food, me);
                }

                qi=query("max_qi", me)*5/100+random(10);
                jing=query("max_jing", me)*5/100+random(10);

                if( query("qi", me)<qi || query("jing", me)<jing )
                {
                        write("你已經感到不行了，冥冥中你覺得有人把你抬到天山腳下。\n");
                        me->move(__DIR__"shanjiao");
                        me->unconcious();
                        return -1;
                }

                me->receive_damage("qi", qi);
                me->receive_damage("jing", jing);
        }

        dest = sprintf("/d/xingxiu/shamo%d", random(10) + 1);
        me->move(dest);
        switch (random(3))
        {
        case 0:
                write("你頂著風沙走啊走，還是沒有走出沙漠。\n");
                break;

        case 1:
                write("你望著漫天遍野的黃沙，嘆了口氣，無精打採的走著。\n");
                break;

        case 2:
                write("你一步步的往前挪著，早已分不出方向。\n");
                break;
        }
        return -1;
}
