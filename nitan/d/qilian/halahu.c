// Room: /d/qilian/hamahu.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "哈拉湖");
        set("long", @LONG
鬱水過玉門關向東，北去二百裡，匯之為澤，名哈拉。傳說有惡蛟
藏在裡面，每年春秋兩季，以肥牛羊十頭祭典才能平安，不然會淫雨連
綿達月余。這裡是方圓八百裡唯一的水源。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"yumen",
                "west"   : __DIR__"yumenguan",
        ]));
        set("coor/x", -17000);
        set("coor/y", 2000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}