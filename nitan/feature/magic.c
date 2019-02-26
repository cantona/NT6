//魔法系統 by wenwu on 2005.9.23

#include <ansi.h>

//魔法防禦(防禦方me,攻擊方ob,造成傷害damage)
int magic_parry(object me,object ob,int damage)
{
        int damage_magic;
if (damage > 0)
{
        switch(me->query("wuxing/mofa"))
        {
                case 0:
                        if (ob->query("wuxing/mofa") == 8)
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(NOR"\n$N的光明力量和$n的黑暗力量以一種極不穩定的形態相互衝撞激盪.....\n"HIW"突然$N身上強光一閃，$N的光明力量似乎擺脱了$n的黑暗力量的束縛在$N身前形成一道光之屏障。\n"NOR,me,ob );
                                        tell_object(me, HIM"你的光明力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(NOR"\n$N的光明力量和$n的黑暗力量以一種極不穩定的形態相互衝撞激盪.....\n突然$n身上的黑暗氣息變得更加深沉，一絲黑氣聚成一條細線直射向$N的前胸。\n"NOR,me,ob );
                                        tell_object(ob, HIM"你的黑暗力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                        }
                        else
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIW"\n$N身上突然流光異彩，一道淡淡的光之屏障擋在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的光明力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage;
                                }
                        }
                        break;

                case 1:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 2)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIY"\n$N身上突然黃光一閃，地之護盾出現在在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的地之力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 4)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIG"\n$n身上青光一閃，$N腳下地面突然裂開，一木樁直直撞向$N下盤。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的木之力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIY"\n$N身上突然黃光一閃，地之盾出現在在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的地之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 2:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 4)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIR"\n$N身上突然紅光一閃，$N身前憑空出現一道火牆。\n"NOR,me);
                                        tell_object(me, HIM"你的火之力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 3)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIW"\n$n身上白光一閃，憑空出現一排水箭徑直向$N射去。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的水之力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIR"\n$N身上突然紅光一閃，一道火之屏障出現在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的火之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 3:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 10)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIW"\n$N身上突然白光一閃，$N身前憑空出現一道水牆。\n"NOR,me);
                                        tell_object(me, HIM"你的水之力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 1)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIY"\n$n身上黃光一閃，$N腳下地面突然突起成錐狀頂向$n。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的土之力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIW"\n$N身上突然白光一閃，一道水之屏障出現在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的水之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 4:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 1)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIG"\n$N身上突然青光一閃，一排參天巨樹擋在了$N的身前。\n"NOR,me);
                                        tell_object(me, HIM"你的木之力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 10)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIY"\n$n身上金芒一閃，一排金劍憑空出現徑直射向$N。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的金之力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIG"\n$N身上突然青光一閃，一排巨木出現在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的木之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 5:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(NOR"\n$N的身影突然變得朦朧，一道旋風憑空捲起護在$N周圍。\n"NOR,me);
                                tell_object(me, HIM"你的氣之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 6:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(HIB"\n$N身上電光閃爍，強大的電流在$N周圍形成一圈薄薄的磁場結界。\n"NOR,me);
                                tell_object(me, HIM"你的雷之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 7:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(HIM"\n$N周身罩上一層淡淡的紫色光暈，一面精神之護盾突然出現在$N身前。\n"NOR,me);
                                tell_object(me, HIM"你的心靈力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 8:
                        if (ob->query("wuxing/mofa") == 0)
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(NOR"\n$N的黑暗力量和$n的光明力量以一種極不穩定的形態相互衝撞激盪.....\n突然$N身上黑暗氣息大盛，$N的黑暗力量衝破了$n光明力量的約束在$N周圍形成一道黑暗天幕。\n"NOR,me,ob );
                                        tell_object(me, HIM"你的黑暗力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(NOR"\n$N的黑暗力量和$n的光明力量以一種極不穩定的形態相互衝撞激盪.....\n突然$n身上強光大盛，一柄光之劍只指$N前胸。\n"NOR,me,ob );
                                        tell_object(ob, HIM"你的光明力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                        }
                        else
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(NOR"\n$N的身影突然變得模糊難見，一層漆黑的霧氣籠罩在$N在身周。\n"NOR,me);
                                        tell_object(me, HIM"你的黑暗力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage;
                                }
                        }
                        break;

                case 9:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(HIC"\n$N的身形突然憑空消失，$N原來所在的位置既然形成一虛無的空間斷層。\n"NOR,me);
                                tell_object(me, HIM"你的空間力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 10:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 1)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIY"\n$N身上突然金芒一閃，$N周身皮膚猶如金鐵質化泛出淡淡金光。\n"NOR,me);
                                        tell_object(me, HIM"你的金之力量額外防禦了"+damage*2/5+"點傷害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 2)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIR"\n$n身上紅光一閃，一道火焰憑空出現徑直卷向$N。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的火之力量造成"+damage*2/5+"點的額外傷害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIY"\n$N身上突然金光一閃，$N周身皮膚猶如銀鐵質化泛出淡淡銀光。\n"NOR,me);
                                        tell_object(me, HIM"你的金之力量額外防禦了"+damage*1/5+"點傷害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                        default:damage_magic = damage;
        }
        return damage_magic;
}
else
        return damage;
}