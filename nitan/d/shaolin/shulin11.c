// Room: /d/shaolin/shulin11.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
你眼前驟然一黑，朦朧中，只見左右前後，到處都是舖天蓋地的
鬆樹林。幾十丈高的大鬆樹簇在一塊，密實的枝葉象一蓬蓬巨傘恆伸
向天空，把陽光遮得絲毫也無。尺把厚的鬆針積在地上，一腳踩下去，
半天拔不出來。你似乎迷失了方向，象沒頭蒼蠅般到處亂闖。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin"+(random(8)+6),
                "south" : __DIR__"shulin"+(random(8)+6),
                "west" : __DIR__"shulin"+(random(8)+6),
                "north" : __DIR__"shulin"+(random(8)+6),
        ]));
        set("no_acc_drop",1);
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
}

void init()
{
        object ob, room;
        mapping fam;

        int i = random(2);
        if( i == 0) return;

        ob = this_player();
        room = this_object();

        if( query("id", ob) == "sengbing" || !living(ob))return ;

        delete("exits", room);

        if( (fam=query("family", ob) )
        && fam["family_name"] == "少林派" 
         && query("guilty", ob) != 1 )
        set("guilty", 3, ob);

        set("startroom", "/d/shaolin/jlyuan", ob);

        message_vision(HIR "\n$N一不小心，走進了僧兵們設下的陷阱！
$N只覺得腳下一陣巨痛，原來是踩上了埋在地下的竹簽。\n\n" NOR, ob);

        message_vision(HIR "\n$N痛得幾乎失去了知覺......\n\n" NOR, ob);

        call_out("trapping", 20, ob, room);

}

void trapping(object ob, object room)
{
        if (! ob || ! living(ob) || environment(ob) != this_object())
                return;

        message_vision(HIY "\n僧兵們把$N從陷井裡起了出來，送進了戒律院！\n\n\n" NOR, ob);
             ob->move(__DIR__"jlyuan"); 

        set("exits/south", __DIR__"shulin"+(random(8)+6), room);
        set("exits/north", __DIR__"shulin"+(random(8)+6), room);
        set("exits/east", __DIR__"shulin"+(random(8)+6), room);
        set("exits/west", __DIR__"shulin"+(random(8)+6), room);
}
