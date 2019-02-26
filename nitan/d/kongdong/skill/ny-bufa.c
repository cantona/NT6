// ny-bufa.c

inherit SKILL;

mapping *action = ({
    ([ "action":"$n縱身一躍，一個「鷂子翻身」，閃身躲了開去。",
       "lian"  :"$N提氣在胸，收腹提肩，一個「鷂子翻身」，高高躍起。",
       "jibie" :5,
       "sen"   :2, ]),
    ([ "action":"$n猛的一個「神龍擺尾」，向後跳開數尺。",
       "lian"  :"$N足下一蹬，一個「神龍擺尾」向後退去，險些扭傷了足踝。",
       "jibie" :10,
       "sen"   :2, ]),
    ([ "action":"$n雙腳輕點，一個「白鶴沖天」，身形向上躥起數尺。",
       "lian"  :"$N雙足一點，一個「白鶴沖天」，躥起三尺來高。",
       "jibie" :20,
       "sen"   :2, ]),
    ([ "action":"$n輕飄飄地向旁邊一閃，$N的凌厲攻勢盡數落在了空裏。",
       "lian"  :"$N把握住身體的平衡，藉着踢腿的力量，向旁邊一躍。",
       "jibie" :30,
       "sen"   :3, ]),
    ([ "action":"$n向高空裏一縱身，躍起五尺來高。",
       "lian"  :"$N向高空裏一縱身，躍起五尺來高。",
       "jibie" :40,
        "sen"  :3, ]),
    ([ "action":"$n躍向空中，一招「蜻蜓點水」，從$N頭上躍了過去。",
       "lian"  :"$N躍起五尺，一招「蜻蜓點水」，輕輕落下地來。",
       "jibie" :50,
       "sen"   :3, ]),
//    ([ "action":"$n低頭側身，蜷腿一縱，向旁邊躍開七尺。",
//       "lian"  :"$N低頭側身，蜷腿一縱，向旁邊躍開七尺。",
//       "jibie" :60,
//       "sen"   :4, ]),
});

int valid_learn(object me)
{
	return 1;
}

int valid_lian(object me)
{
//    int encu;
//    encu = me->query_encumbrance() * 100 / me->query_max_encumbrance();
//    if ( encu < 10 )
//        return notify_fail("輕功必須負重練習。\n");
    return 1;
}

mapping query_action(int jibie)
{
    int i, size;

    size = sizeof( action );
    for ( i = 0; i < sizeof( action ); i++ )
        if ( action[ i ][ "jibie" ] > jibie )
        {
            size = i;
            break;
        }
    return action[ random( size ) ];
}

string query_xiuwei_type()
{
    return "dodge";
}

// 返回這路武功的等級, 第一等返回 1, 第十等返回 10.
int query_dengji()
{
	return 2;
}

