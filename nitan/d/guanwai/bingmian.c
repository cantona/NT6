// /guanwai/bingmian.c

inherit ROOM;

void create()
{
        set("short", "冰面");
        set("long", @LONG
這裡是鬆花江的江面，現已凍成了幾尺厚的堅冰。行人或馬匹，車輛均
可橫逾江面而絕無危險。冰面上留有厚厚的積雪，與兩岸連成一片，只有中
間經常行走之出，露出一條青色的冰路。
LONG );
        set("exits", ([
                "east"  : __DIR__"damenkan",
                "west"  : __DIR__"chuanchang",
        ]));
        set("outdoors", "guanwai");
        setup();
}

int valid_leave(object me, string dir)
{
        object obj;
        int i;

        switch (NATURE_D->query_month())
        {
        case 11: case 12: case 1: case 2: case 3: case 4:
                message_vision("$N踩在冰面上趕路，腳下吱嘎吱嘎的響。\n\n", me);
                if (random(me->query_dex()) + me->query_dex() / 2 < 20)
                {
                        me->receive_wound("qi", 20);
                        me->receive_damage("qi", 10);
                        message_vision("$N只覺得腳下一滑，全身騰空而起，結結實實的摔在了冰面上！\n", me);
                }
                break;
        default:
                set_temp("die_reason", "因為冰面開凍，掉到江裡面淹死了", me);
                me->die();
                write("以後可要注意啦！\n");
                return -1;
        }
        return 1;
}