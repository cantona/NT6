// shufang.c 盤龍居書房

#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "書房");
        set("long", @LONG
這裡是盤龍居的主人讀書寫字的地方，幹凈明亮。文房四寶整整齊齊
的擺在桌子上面。有時主人也在這裡簽發一些邀請客人的請柬。
LONG );

        set("default_long", "這裡是ROOM_NAME的主人ROOM_OWNER讀書寫字的"/* EXAMPLE */
                            "地方，幹凈明亮。文房四寶整整齊齊的擺在桌" /* EXAMPLE */
                            "子上面。有時ROOM_OWNER也在這裡簽發(sign"/* EXAMPLE */
                            ")一些邀請客人的請柬。");                  /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "east" : __DIR__"jusuo",
        ]));

        set("sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    add_action("do_sign", "sign");
}

int do_sign()
{
        object ob;
        object me;

        me = this_player();

//**        if (! is_room_owner(me))
//**                return notify_fail("你又不是這兒的主人，亂搞"
//**                                   "什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在還忙著呢。\n");

        message_vision("$N抽過一張紙，拿起筆來，在上面畫符似"
                       "的寫了些東西。\n", me);
        tell_object(me, "你寫好一份手諭。\n");

        ob = new("/d/room/roomobj/pass");
        ob->set_name(HIW+query("name", me)+"手諭"NOR,
                     ({ "pass", query("room_owner_id") + " pass" }));
        ob->set("long","一張由"+query("name",me)+"親筆簽發的"+
                     "手諭，憑借它你可以進出" + query("room_name") +
                     "。\n");
        ob->move(me);
        me->start_busy(4 + random(4));
        return 1;
}