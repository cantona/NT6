// Room: /d/luoyang/guanlin.c
// Last modified by winder 2002.11.11

#include <ansi.h>;
inherit  ROOM;

void  create  ()
{
        set("short",  "關林");
        set("long",  @LONG
此處位於洛陽城南十四里處。關林始建於唐，相傳為三國蜀將關羽
首級的葬地，前為祠廟，後為墓冢，冢高五丈有餘，千株參天翠柏，蔚
然成林，故稱“關林”。明萬曆年間始建廟植鬆。清乾隆時又加擴建，
致成現今的規模。關林總面積約百畝左右，三大殿和鐘鼓樓，紅牆碧瓦，
雕樑畫棟，建築嚴整。大殿塑有關羽着帝王裝像，二殿為戎裝像，東殿
為關羽睡卧像，西殿為秉燭誦《春秋》像，大殿前廊有複製八十三斤重
的青龍偃月刀一把。古柏蒼鬱，殿宇堂皇，隆冢巨碑，上書“忠義神武
關聖大帝”，氣象幽然。
    常有江湖義士來此拜祭。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"      :  __DIR__"guandaos2",
        ]));
        set("objects",  ([
                __DIR__"obj/xiang" : 1,
        ]));
        set("no_fight", 1);
        set("no_beg", 1);
        set("outdoors", "luoyang");
	set("coor/x", -6980);
	set("coor/y", 2080);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_ketou","ketou");
        add_action("do_ketou","kneel");
}

int do_ketou()
{
        object *inv, pai, me = this_player();
        string partynm;
        int i, j, mylvl, oblvl;

        if( !query("party", me) )
                return notify_fail("你不屬於任何幫會！\n");
        if( !query("party/player", me) )
                return notify_fail("玩家創立的幫會才能領取腰牌！\n");
        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成！\n");

        inv = all_inventory(me);
        i = sizeof(inv);
        for (j = 0; j < i; j++)
        {
                if( query("id", inv[j]) == "yaopai" )
                        return notify_fail("你恭恭敬敬地磕了卅響頭，一點風聲也沒有！\n");
        }
        message_vision(HIG"$N屈膝跪下，一個響頭恭敬地磕了下去。猛然間，一陣狂風颳地而來，只聽“啪”的一聲，松枝上掉下一塊腰牌，正落在$N懷裏！也不知道是哪個調皮鬼掛在上面的。\n"NOR, me);
        pai = new("/d/luoyang/obj/yaopai");
        pai -> move(me);
        return 1;
}