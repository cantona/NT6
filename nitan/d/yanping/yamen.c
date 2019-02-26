// Room: /d/yanping/yamen.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "府衙");
        set("long", @LONG
延平府治南平縣，設於東漢建安元年，取漢王朝派兵入閩平定南疆
之意。大宋文天祥曾在此設都督府，不屈抗元，留名汗青。開台聖王鄭
成功，永曆十三年，受南明永曆皇帝（桂王）賜封延平郡王。後仕於南
明隆武皇帝，賜“宋”姓，民間習稱“國姓爺”。
    這裏便是延平府的大衙。堂上兩排水火無情棍拱着“肅靜”、“回
避”二牌，樑上也是不能免俗的“明鏡高懸”四字牌匾。
LONG );
        set("exits", ([
                "south" : __DIR__"road2",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 2,
        ]));
        set("coor/x", 1480);
        set("coor/y", -6180);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}