inherit ROOM;

void create()
{
              set("short", "九老洞口");
        set("long", @LONG
九老洞在仙峯寺外。傳説遠古時候，有九位仙叟住在這個洞裏，
不知他們生於何年，終於何年。軒轅皇帝訪道於此，見一老叟，問曰：
有侶乎？答曰：九人。這是九老洞的來歷。這個洞很深，很少有人進
去，只有些人站在洞口談笑呼叫。這裏向西經九十九道拐到千佛庵，
一路向北到蓮花石。
LONG );
              set("objects", ([
                   "/clone/quarry/hou" : 2,
              ]));
              set("outdoors", "emei");
              set("exits", ([
                  "east"      : __DIR__"jsjdg4",
                  "enter"     : __DIR__"jiulaodong",
                  "northwest" : __DIR__"lianhuashi",
              ]));
        set("coor/x", -520);
        set("coor/y", -250);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}