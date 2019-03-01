// Room: /d/shaolin/zhonglou3.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鐘樓三層");
        set("long", @LONG
塔身往上似乎越來越窄，樓梯也漸為擠仄。扶手上不少朽壞處續
接了新木，漆色也是新舊不同。從窗孔往外望，往北可以看到竹林中
的藏經樓和方丈樓露出飛檐一角，往西則是後殿的屋頂，屋脊上塑了
個大大的『佛』字。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou4",
                "down" : __DIR__"zhonglou2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
