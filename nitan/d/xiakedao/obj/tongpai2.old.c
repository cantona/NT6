//tongpai1.c
//edit by noz

inherit ITEM;

void create()
{
  set_name( "罰惡銅牌",({"e pai"}));
  set_weight(100);

  if( clonep() )
        set_default_object(__FILE__);

  set("unit", "塊");
  set("long", "這是一塊閃閃發光的白銅片子，約有巴掌大小，牌子正面刻着一張猙獰的煞神兇臉，十分詭異。\n");
  set("value", 100);

  setup();
}
