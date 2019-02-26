inherit ROOM;

void create()
{
      set("short","白龍洞");
        set("long", @LONG
白龍洞據説是「白蛇傳」中的白娘子修煉成仙之處。這裏楠木參
天，林蔭夾道，株株秀挺俊何，枝葉分披上捧，如兩手擁佛，傳為古
時一高僧按「法華經」口誦一字植樹一株，共植六萬九千七百七十七
株，時稱古德林。這裏北上至萬年庵，南下是清音閣。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "east"      : __DIR__"qingyinge",
          "west"      : __DIR__"gudelin2",
          "northup"   : __DIR__"wannianan",
          "southeast" : __DIR__"gudelin1",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -470);
        set("coor/y", -230);
        set("coor/z", 80);
        setup();
      replace_program(ROOM);
}