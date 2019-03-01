inherit ROOM;

void create()
{
      set("short","華嚴頂");
        set("long", @LONG
華嚴頂挺拔高峭，古剎雲深，殿宇孤聳，風景奇險。這裡視野開
闊，仰可見金頂巍巍，俯可望群峰羅列，許多蹲伏山間的寺院也在眼
底。由此向西過數坡，即到蓮花石，東下過十二盤可到萬年寺。北面
是一間馬廄。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/li" : 1,
           __DIR__"npc/girldizi" : 1,
      ]));
      set("outdoors", "emei");
      set("exits", ([
          "north"    : __DIR__"majiu2",
          "westup"   : __DIR__"lianhuashi",
          "eastdown" : __DIR__"shierpan4",
      ]));
        set("coor/x", -520);
        set("coor/y", -240);
        set("coor/z", 120);
        setup();
      replace_program(ROOM);
}