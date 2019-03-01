inherit ROOM;

void create()
{
      set("short", "黑龍江棧道");
        set("long", @LONG
黑龍江棧道沿黑龍江而建。這裡一山中開，兩崖並立，形成一道
寬僅數尺，長達幾百米的深峽──白雲峽。黑龍江棧道就從狹窄的白
雲峽中轉折穿過，架設在絕壁上。走在棧道上只覺道窄人危；俯視深
澗，急流飛旋，山靜而覺動；仰觀頭頂天光如隙，崖開而欲合。這就
是天開畫圖的「一線天」。棧道南通千佛庵，北至清音閣。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "south" : __DIR__"heilong2",
          "north" : __DIR__"qingyinge",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -460);
        set("coor/y", -230);
        set("coor/z", 100);
        setup();
      replace_program(ROOM);
}