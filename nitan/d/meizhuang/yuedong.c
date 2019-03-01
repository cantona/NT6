inherit ROOM;

void create()
{
        set("short", "月洞門");
        set("long", @LONG
你穿過走廊，來到一個月洞門前。月洞門門額上寫著『琴心』兩
字，以藍色琉璃砌成，筆致蒼勁，當是出于禿筆翁的手筆了。過了月
洞門，是一條清幽的花徑，兩旁修竹姍姍，花徑鵝卵石上生滿青苔，
顯得平素少有人行。
LONG );
        set("exits", ([
            "north" : __DIR__"xiaoyuan",
            "south" : __DIR__"xiaodao",
        ]));

        set("outdoors", "meizhuang");

        setup();
        replace_program(ROOM);
}