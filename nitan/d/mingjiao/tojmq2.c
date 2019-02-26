//TORJQ2.C

inherit ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
這裏大道平坦，地勢開闊，兩旁樹林中鳥語花香，一片和平安祥
的氣氛。此時又有誰能想到，這條大道上撒下過多少江湖中人的血，
這片林中又埋有多少慘死於武林爭鬥的冤魂的骨。遠處，隱約傳來叮
叮咚咚的伐木聲，偶爾能讓人追憶起刀戈鐵馬的沙場景象。
LONG );
        set("exits", ([
                "northwest" : __DIR__"tojmq3",
                "southeast" : __DIR__"tojmq1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}