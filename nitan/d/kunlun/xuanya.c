// Room: /d/kunlun/xuanya.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;
int do_jump(string arg);
void create()
{
        set("short", HIY"懸崖"NOR);
        set("long", @LONG
你來到懸崖之上，突然在對而傳來幾聲狼嗥，甚是淒厲可怖。只見
對面幾隻大灰狼仰起頭，向着你張牙舞爪的嗥叫，想是要食之果腹，只
是之間有一條深不見底的萬丈峽谷，無法過來。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
                "eastdown" : __DIR__"xschongling1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hongmei");
        set("coor/x", -100030);
        set("coor/y", 20010);
        set("coor/z", 70);
        setup();
}
void init()
{
        add_action("do_jump","jump");
}
int do_jump(string arg)
{
        object me;
        me = this_player();
        if( arg=="down" &&me->query_kar()>=20)
        {
                if (me->query_skill("dodge",1)>=50)
                {
                        message("vision", me->name() + "一個縱身，跳下了懸崖。\n", environment(me), ({me}) );
                        write(HIR"\n你向下一跳，直向萬丈深淵掉去！！！\n\n"NOR);
                        write(HIR"\n你下落的速度太快，衝開瀰漫之霧，直向下墮！！！\n\n"NOR);
                        write(HIR"\n你只覺身旁風聲虎虎，身子不斷的向下摔落......\n偶爾見到峭壁上有樹枝伸出，便想去抓，但下落之\n力太大，樹枝喀喇的一聲斷了！！！\n\n"NOR);
                        write(HIY"\n但，你的下落速度慢了一點，急忙使一招“烏龍絞柱”，牢牢的抱住了松樹。\n\n"NOR);
                        me->move(__DIR__"songshu");
                        message("vision", me->name() + "死死的抱住了這棵小松樹。\n", environment(me), ({me}) );
                }
                else {
                        message("vision", me->name() + "一個縱身，跳下了懸崖。\n", environment(me), ({me}) );
                        write(HIR"\n你向下一跳，直向萬丈深淵掉去！！！\n\n"NOR);
                        write(HIR"\n你下落的速度太快，衝開瀰漫之霧，直向下墮！！！\n\n"NOR);
                        write(HIR"\n你只覺身旁風聲虎虎，身子不斷的向下摔落......\n偶爾見到峭壁上有樹枝伸出，便想去抓，但下落之\n力太大，樹枝喀喇的一聲斷了！！！\n"NOR);
                        write(HIR"\n                ."NOR);
                        write(HIR"\n                ."NOR);
                        write(HIR"\n                .\n\n"NOR);
                        me->move(__DIR__"xuedi");
                        me->unconcious();
                               message("vision", me->name() + "從懸崖上摔了下來。\n", environment(me), ({me}) );
                }
                return 1;
        }
        if( arg=="down" &&me->query_kar()<20)
        {
                if (me->query_skill("dodge",1)>=20)
                {
                        message("vision", me->name() + "一個縱身，跳下了懸崖。\n", environment(me), ({me}) );
                        write(HIR"\n你向下一跳，直向萬丈深淵掉去！！！\n\n"NOR);
                        write(HIR"\n你下落的速度太快，衝開瀰漫之霧，直向下墮！！！\n\n"NOR);
                        write(HIR"\n你只覺身旁風聲虎虎，身子不斷的向下摔落......\n偶爾見到峭壁上有樹枝伸出，便想去抓，但下落之\n力太大，樹枝喀喇的一聲斷了！！！\n"NOR);
                        write(HIR"\n                ."NOR);
                        write(HIR"\n                ."NOR);
                        write(HIR"\n                .\n\n"NOR);
                        me->move(__DIR__"xuedi");
                        me->unconcious();
                        message("vision", me->name() + "從懸崖上摔了下來。\n", environment(me), ({me}) );
                }
                else
                {
                        message("vision", me->name() + "一個縱身，跳下了懸崖。\n", environment(me), ({me}) );
                        write(HIR"\n你向下一跳，直向萬丈深淵掉去！！！\n\n"NOR);
                        write(HIR"\n你下落的速度太快，衝開瀰漫之霧，直向下墮！！！\n\n"NOR);
                        write(HIR"\n你只覺身旁風聲虎虎，身子不斷的向下摔落......\n偶爾見到峭壁上有樹枝伸出，便想去抓，但下落之\n力太大，樹枝喀喇的一聲斷了！！！\n"NOR);
                        write(HIR"\n                ."NOR);
                        write(HIR"\n                ."NOR);
                        write(HIR"\n                .\n\n"NOR);
                        me->move(__DIR__"xuedi");
                        set_temp("last_damage_from", "跳下懸崖"+"摔", me);
                        me->die();
                        message("vision", me->name() + "從懸崖上摔了下來。\n", environment(me), ({me}) );
                }
                return 1;
        }
}
