inherit ROOM;

void create()
{
      set("short", "華藏庵後殿");
        set("long", @LONG
這是峨嵋山華藏庵的後殿。是峨嵋派掌門人傳教弟子功夫的地方。
這裏供有一尊普賢菩薩像。兩旁靠牆放着幾張太師椅地上放着幾個蒲
團。掌門人正在向幾個女弟子傳授武功。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/miejue" : 1,
      ]));
      set("no_get_from", 1);
      set("no_get", 1);
      set("no_steal", 1);
      set("no_clean_up", 0);
      set("exits", ([
          "north"   : __DIR__"hcadadian", 
      ]));
      setup();
      replace_program(ROOM);
}