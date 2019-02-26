inherit ROOM;

void create()
{
      set("short", "解脱坡");
        set("long", @LONG
這裏是峨嵋勝地解脱坡。坡下一座小橋，叫解脱橋。行人至此，
坐橋上聽泉聲甚美。當此良辰美景，心無芥蒂，心即解脱。坡上一座
庵堂，東下一片密林。橋下山溪向東流淌到報國寺的西面。
LONG );
      set("exits", ([
          "eastdown" : __DIR__"milin2",
          "westup"   : __DIR__"guanyintang",
      ]));
      set("outdoors", "emei");
      set("no_clean_up", 0);
        set("coor/x", -400);
        set("coor/y", -230);
        set("coor/z", 30);
        setup();
      replace_program(ROOM);
}