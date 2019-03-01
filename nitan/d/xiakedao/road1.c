// /d/xiakedao/road1.c 俠客島 山路1

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
走在青石鋪成的小路上，腳步十分輕捷。兩旁都是密林，枝葉遮
天蔽日，陰沉沉的很不舒服。林中鳥雀嘰喳，與呼呼的風聲混成一片。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"road2",
                "northdown" :__DIR__"shanmen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -22020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}