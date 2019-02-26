inherit ROOM;

void create()
{
      set("short","九十九道拐");
        set("long", @LONG
這是著名的「九十九道拐」，道路紆曲陡豎千折百回。據説過去
曾有個百餘歲的瘋僧至此，見一巨蟒擋路，便唸咒驅蟒。但人們得知
此處有巨蟒出沒後，便再無人敢碰這裏的草木，並以「龍居」名之。
由此東可至千佛庵，西達九老洞。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown" : __DIR__"jsjdg3",
          "west"     : __DIR__"jldongkou",
      ]));
        set("coor/x", -510);
        set("coor/y", -250);
        set("coor/z", 130);
        setup();
      replace_program(ROOM);
}