inherit ROOM;

void create()
{
        set("short", "亂墳崗");
        set("long", @LONG
這裏一片都是墳墓，不知道埋了多少英雄好漢，多少鉅奸
大惡，讓人不禁生出了人生不過如此的悲涼之意。不過如煙火
一樣，即便是短暫也能發出眩目的光彩，一念及此，你不由收
起悲觀的念頭，熱血澎湃，恨不得立即投身江湖快意恩仇，去
爭取名垂青史。
LONG);
        set("exits", ([
                "northwest" : __DIR__"luanshigang",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        setup();

        replace_program(ROOM);
}