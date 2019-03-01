//room: /d/mingjiao/qiandian.c
inherit ROOM;

void init();

void create()
{
        set("short","明教前殿");
        set("long", @LONG
你來到這裡，放眼窗外望去，漫漫昆侖雪山，晶瑩剔透，蒼天浩
浩，白雲悠悠。東方沃野千裡，楚天遼闊；西面高山巍巍，迤邐萬裡。
這裡就是叱□武林八百年的明教總舵的前殿。
LONG );
       set("exits",([
           "east"      : __DIR__"eastdian",
           "west"      : __DIR__"westdian",
           "north"     : __DIR__"dadian",
           "southdown" : __DIR__"square",
       ]));
       setup();
       replace_program(ROOM);
}
