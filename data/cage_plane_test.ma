//Maya ASCII 2025ff03 scene
//Name: cage_plane_test.ma
//Last modified: Thu, Jul 10, 2025 06:55:19 PM
//Codeset: 1252
requires maya "2025ff03";
requires "mtoa" "5.4.5";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2025";
fileInfo "version" "2025";
fileInfo "cutIdentifier" "202409190603-cbdc5a7e54";
fileInfo "osv" "Windows 11 Education v2009 (Build: 22631)";
fileInfo "UUID" "309390F1-4C4F-5EB1-5229-B99ED35277BA";
fileInfo "license" "education";
createNode transform -s -n "persp";
	rename -uid "E3178EDC-4813-88F9-D4B2-7EA764CAF382";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -0.19974413688502871 21.819197040931531 18.598317013671736 ;
	setAttr ".r" -type "double3" -51.338352729615508 0.99999999999937705 -1.491112110532821e-16 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "299FE85C-498F-AF22-6547-84AB18838EF2";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 29.801508332262149;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "0F3BC8A5-44FC-DBAB-CC0A-45A264C7C98F";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -0.053465911441536118 1000.1 0.20347653598009335 ;
	setAttr ".r" -type "double3" -90 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "4AFF6C76-4E7A-9A0C-9BEC-DF8D766CC264";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 35.243876464990983;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "front";
	rename -uid "173266C6-40FC-6739-CCF8-758AB39A3400";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "DA815E26-43B2-D584-A528-D5AEFB08B391";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "side";
	rename -uid "0228969F-4728-9229-68DF-C082AB088937";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 90 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "92547FA8-455C-2821-9D73-D08B563954EB";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -n "test_cage";
	rename -uid "00B05BCB-4B53-3D43-9502-42826F1D4132";
createNode transform -n "test_cage_display" -p "test_cage";
	rename -uid "D6EBE87F-4A7C-1665-19C3-0CB943F31BFC";
createNode transform -n "test_cage_anchor_0_handle_display" -p "test_cage_display";
	rename -uid "BD150BF2-4816-4B07-0E17-F08AA0DEF509";
createNode transform -n "test_cage_anchor_0_handle_0_display_crv" -p "test_cage_anchor_0_handle_display";
	rename -uid "0327E1E2-44AF-8740-1F8A-FFB5986264C4";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape1" -p "test_cage_anchor_0_handle_0_display_crv";
	rename -uid "69B35568-41CF-1278-D47A-98940BB52CCE";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		2.3333333653339716 0 5.3780633851863158e-07
		;
createNode transform -n "test_cage_anchor_0_handle_1_display_crv" -p "test_cage_anchor_0_handle_display";
	rename -uid "12DFBB1A-4C7A-8FF8-2D47-E299306B89F3";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape11" -p "test_cage_anchor_0_handle_1_display_crv";
	rename -uid "B7D3A7A2-4084-1792-0E39-47B66C373E03";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		-1.053041372796764e-07 0 -2.3333322621184527
		;
createNode transform -n "test_cage_anchor_0_handle_2_display_crv" -p "test_cage_anchor_0_handle_display";
	rename -uid "FC055564-45A6-F383-2D28-68899E30EDB3";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape13" -p "test_cage_anchor_0_handle_2_display_crv";
	rename -uid "83C54653-4A0C-B0B5-9EED-819AF9A6AB5F";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		-2.3333334568278854 0 5.3335950658817133e-07
		;
createNode transform -n "test_cage_anchor_0_handle_3_display_crv" -p "test_cage_anchor_0_handle_display";
	rename -uid "4E0AB2EC-470B-E5C3-B395-C1AE0C4E036A";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape29" -p "test_cage_anchor_0_handle_3_display_crv";
	rename -uid "52164DB0-48E5-E471-03E0-788A2E0B7429";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		-3.1154839404292335e-08 0 2.33333391351945
		;
createNode transform -n "test_cage_anchor_1_handle_display" -p "test_cage_display";
	rename -uid "F20AC206-49C0-0B51-B0D3-F89862FAE407";
createNode transform -n "test_cage_anchor_1_handle_0_display_crv" -p "test_cage_anchor_1_handle_display";
	rename -uid "1DB98201-42B2-89BA-84DD-76BF5AD42A54";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape2" -p "test_cage_anchor_1_handle_0_display_crv";
	rename -uid "7FD1CC6C-4D77-141C-4C32-BEAC3305127A";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 0
		4.6666662773083312 0 1.0910754679877011e-06
		;
createNode transform -n "test_cage_anchor_1_handle_1_display_crv" -p "test_cage_anchor_1_handle_display";
	rename -uid "5E405F38-42BA-1350-4C2B-048C74A6F817";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape4" -p "test_cage_anchor_1_handle_1_display_crv";
	rename -uid "7D993C07-4149-0AE4-92C9-B79DB8CE4A31";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 0
		6.9999993322580369 0 -2.3333327688374745
		;
createNode transform -n "test_cage_anchor_1_handle_2_display_crv" -p "test_cage_anchor_1_handle_display";
	rename -uid "8DBCF4DF-47C5-C6EA-B581-1EBC4F06C16A";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape22" -p "test_cage_anchor_1_handle_2_display_crv";
	rename -uid "F818BA44-411D-0074-96F4-E7A82AE7C3F2";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 0
		6.9999991248986788 0 2.3333341869248376
		;
createNode transform -n "test_cage_edge_display" -p "test_cage_display";
	rename -uid "08E3F633-4054-6B21-0526-F087C626196E";
createNode transform -n "test_cage_edge_1_display_crv" -p "test_cage_edge_display";
	rename -uid "8810BCF1-4135-4CAB-D93B-46BFB8BF6F36";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape3" -p "test_cage_edge_1_display_crv";
	rename -uid "E7D5AE87-45C5-C90D-36DA-8995CF82F228";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		0 0 0
		2.3333333653339716 0 5.3780633851863158e-07
		4.6666662773083312 0 1.0910754679877011e-06
		7 0 0
		;
createNode transform -n "test_cage_edge_2_display_crv" -p "test_cage_edge_display";
	rename -uid "7B7569F4-4BF1-FDE4-74C1-C99FD9EDDC49";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape6" -p "test_cage_edge_2_display_crv";
	rename -uid "2A0A7698-4653-7859-7AC3-9CB427D98A9C";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		7 0 0
		6.9999993322580369 0 -2.3333327688374745
		6.9999995699620889 0 -4.6666648508466322
		7 0 -7
		;
createNode transform -n "test_cage_edge_3_display_crv" -p "test_cage_edge_display";
	rename -uid "F02018BA-4F5B-4078-FC1E-5A917B4959C3";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape9" -p "test_cage_edge_3_display_crv";
	rename -uid "BAA48AEA-4ED2-048D-E9D5-0AAAE7128C4D";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		7 0 -7
		4.6666666344585144 0 -6.9999999932443462
		2.3333333588809921 0 -6.9999999932443515
		0 0 -7
		;
createNode transform -n "test_cage_edge_4_display_crv" -p "test_cage_edge_display";
	rename -uid "DFE1CC54-4232-35C8-9BE4-318F895CCCAF";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape12" -p "test_cage_edge_4_display_crv";
	rename -uid "FD3474B0-434C-46DA-A395-BD86E3B2F69F";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		0 0 -7
		1.2575157539212984e-08 0 -4.6666661455102991
		-1.053041372796764e-07 0 -2.3333322621184527
		0 0 0
		;
createNode transform -n "test_cage_edge_5_display_crv" -p "test_cage_edge_display";
	rename -uid "65A110F4-4012-387B-C665-46B31F9EE286";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape15" -p "test_cage_edge_5_display_crv";
	rename -uid "2C054470-4612-DB7E-DE8F-C9AF22573CD9";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		0 0 0
		-2.3333334568278854 0 5.3335950658817133e-07
		-4.6666661391802515 0 1.4535012517191692e-06
		-7 0 0
		;
createNode transform -n "test_cage_edge_6_display_crv" -p "test_cage_edge_display";
	rename -uid "FEFE81B9-4931-FE90-6E39-BBA79A07D1FC";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape18" -p "test_cage_edge_6_display_crv";
	rename -uid "FF6277E9-437B-EC1A-C566-919425B81647";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		-7 0 0
		-6.9999996457418678 0 -2.3333320200869738
		-6.9999995979861156 0 -4.6666656863033431
		-7 0 -7
		;
createNode transform -n "test_cage_edge_7_display_crv" -p "test_cage_edge_display";
	rename -uid "9E3ED71C-411E-E473-8D6A-D78992091CBD";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape21" -p "test_cage_edge_7_display_crv";
	rename -uid "BC81B832-4A1F-E105-BEB0-A99624416BC1";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		-7 0 -7
		-4.6666666344585144 0 -6.9999999932443462
		-2.3333333588809921 0 -6.9999999932443515
		0 0 -7
		;
createNode transform -n "test_cage_edge_8_display_crv" -p "test_cage_edge_display";
	rename -uid "C6793902-4ABA-6AEA-BB53-9789586E7044";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape24" -p "test_cage_edge_8_display_crv";
	rename -uid "1B541273-4C4F-DFAD-DB94-D6905FBF4331";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		7 0 0
		6.9999991248986788 0 2.3333341869248376
		6.9999996322473912 0 4.6666669039576609
		7 0 7
		;
createNode transform -n "test_cage_edge_9_display_crv" -p "test_cage_edge_display";
	rename -uid "EA52F582-4A8A-D956-DEE2-1A8302675EEF";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape27" -p "test_cage_edge_9_display_crv";
	rename -uid "2723B70A-401C-8D93-721B-46B3CD9DC21F";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		7 0 7
		4.6666664392498474 0 7.0000002105699295
		2.3333331824980976 0 7.0000009529283833
		0 0 7
		;
createNode transform -n "test_cage_edge_10_display_crv" -p "test_cage_edge_display";
	rename -uid "B4BF0287-4E8D-D5E6-46A4-37B88F271BEA";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape30" -p "test_cage_edge_10_display_crv";
	rename -uid "FD993DC7-4438-461C-DD33-55A3930B05EC";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		0 0 7
		-2.4659382630076931e-08 0 4.6666673031694783
		-3.1154839404292335e-08 0 2.33333391351945
		0 0 0
		;
createNode transform -n "test_cage_edge_11_display_crv" -p "test_cage_edge_display";
	rename -uid "D72A9504-4E1E-3CC6-BBAA-4DB6C49D8053";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape33" -p "test_cage_edge_11_display_crv";
	rename -uid "0B4087FD-4457-DF52-B232-38AB7B9150C0";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		0 0 7
		-2.3333333959499063 0 7.0000003367088386
		-4.6666662185767738 0 7.000000717466337
		-7 0 7
		;
createNode transform -n "test_cage_edge_12_display_crv" -p "test_cage_edge_display";
	rename -uid "3B0E436A-40AA-AF8F-2E09-6187161B42F3";
	setAttr ".ovdt" 1;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape36" -p "test_cage_edge_12_display_crv";
	rename -uid "33682A98-4EA2-0C4C-BC5F-9FABCE8A6138";
	setAttr -k off ".v";
	setAttr -s 4 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		3 1 0 no 3
		6 0 0 0 1 1 1
		4
		-7 0 7
		-6.9999993982017994 0 4.6666670782768653
		-6.9999998722726584 0 2.3333342709237779
		-7 0 0
		;
createNode transform -n "test_cage_anchor_2_handle_display" -p "test_cage_display";
	rename -uid "BD6EBF81-4667-8BCD-4611-2BBD099E82E2";
createNode transform -n "test_cage_anchor_2_handle_0_display_crv" -p "test_cage_anchor_2_handle_display";
	rename -uid "880377AE-4131-04B3-A54E-6E9CBFD1FB1E";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape5" -p "test_cage_anchor_2_handle_0_display_crv";
	rename -uid "F615E1E5-40AA-B532-F258-94A4A59E25B1";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 -7
		6.9999995699620889 0 -4.6666648508466322
		;
createNode transform -n "test_cage_anchor_2_handle_1_display_crv" -p "test_cage_anchor_2_handle_display";
	rename -uid "A19BFDFC-48B5-0542-2449-2781A43AF67B";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape7" -p "test_cage_anchor_2_handle_1_display_crv";
	rename -uid "5A545AB2-49EC-BF7A-4B1A-6883DB6130FA";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 -7
		4.6666666344585144 0 -6.9999999932443462
		;
createNode transform -n "test_cage_anchor_3_handle_display" -p "test_cage_display";
	rename -uid "91886664-4ABC-1E4B-CCE9-7BB034AFCA7B";
createNode transform -n "test_cage_anchor_3_handle_0_display_crv" -p "test_cage_anchor_3_handle_display";
	rename -uid "759C343B-451A-D4E6-1B9D-9DB48EBA730F";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape8" -p "test_cage_anchor_3_handle_0_display_crv";
	rename -uid "985F736F-41D3-9B4A-4932-3385E631488C";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 -7
		2.3333333588809921 0 -6.9999999932443515
		;
createNode transform -n "test_cage_anchor_3_handle_1_display_crv" -p "test_cage_anchor_3_handle_display";
	rename -uid "FDC7333A-4C75-C7B8-A1AC-06976E553977";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape10" -p "test_cage_anchor_3_handle_1_display_crv";
	rename -uid "4410034C-4BBF-5BB3-3C4A-01A8BF9AD1D5";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 -7
		1.2575157539212984e-08 0 -4.6666661455102991
		;
createNode transform -n "test_cage_anchor_3_handle_2_display_crv" -p "test_cage_anchor_3_handle_display";
	rename -uid "0E70E013-42E4-A3C3-6669-3E9421F7CF58";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape20" -p "test_cage_anchor_3_handle_2_display_crv";
	rename -uid "FC4FAD27-48EE-9C28-25EB-6A95BD80A0BC";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 -7
		-2.3333333588809921 0 -6.9999999932443515
		;
createNode transform -n "test_cage_anchor_4_handle_display" -p "test_cage_display";
	rename -uid "17910A39-4CCC-1E8F-92C7-C7B1BA3083EF";
createNode transform -n "test_cage_anchor_4_handle_0_display_crv" -p "test_cage_anchor_4_handle_display";
	rename -uid "08D62EF3-46A4-4D59-C634-9F9E62385C76";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape14" -p "test_cage_anchor_4_handle_0_display_crv";
	rename -uid "F414B2B4-40CF-5017-1B55-E799AE8937E5";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 0
		-4.6666661391802515 0 1.4535012517191692e-06
		;
createNode transform -n "test_cage_anchor_4_handle_1_display_crv" -p "test_cage_anchor_4_handle_display";
	rename -uid "DC97C28C-4E0B-0B1C-E8A6-12A7631E330C";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape16" -p "test_cage_anchor_4_handle_1_display_crv";
	rename -uid "971307F9-43E1-83C3-F1EB-94A1D14C3E35";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 0
		-6.9999996457418678 0 -2.3333320200869738
		;
createNode transform -n "test_cage_anchor_4_handle_2_display_crv" -p "test_cage_anchor_4_handle_display";
	rename -uid "3CCD3081-449B-4C12-BABF-7BA800C256AB";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape35" -p "test_cage_anchor_4_handle_2_display_crv";
	rename -uid "2E2BAFFA-4A94-7F52-B7E3-A5B6CB72E916";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 0
		-6.9999998722726584 0 2.3333342709237779
		;
createNode transform -n "test_cage_anchor_5_handle_display" -p "test_cage_display";
	rename -uid "05C4192B-412B-1675-FB93-B9A15259443B";
createNode transform -n "test_cage_anchor_5_handle_0_display_crv" -p "test_cage_anchor_5_handle_display";
	rename -uid "C2EB1150-4AD3-ED55-C02A-28A409ED6511";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape17" -p "test_cage_anchor_5_handle_0_display_crv";
	rename -uid "239B443E-4E21-08DB-C3FE-2FBB82792196";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 -7
		-6.9999995979861156 0 -4.6666656863033431
		;
createNode transform -n "test_cage_anchor_5_handle_1_display_crv" -p "test_cage_anchor_5_handle_display";
	rename -uid "56B0DFCA-49CF-79B5-88B7-B48769D1AE13";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape19" -p "test_cage_anchor_5_handle_1_display_crv";
	rename -uid "DF07668B-4DAA-97B0-3279-AE9CF1D9AC33";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 -7
		-4.6666666344585144 0 -6.9999999932443462
		;
createNode transform -n "test_cage_anchor_6_handle_display" -p "test_cage_display";
	rename -uid "E6645E5B-4224-E0E3-0389-9BB86A830BEA";
createNode transform -n "test_cage_anchor_6_handle_0_display_crv" -p "test_cage_anchor_6_handle_display";
	rename -uid "1E5CC157-4F51-674D-BF21-39B9F399DE29";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape23" -p "test_cage_anchor_6_handle_0_display_crv";
	rename -uid "612F424A-4D29-9094-F13E-88A956372843";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 7
		6.9999996322473912 0 4.6666669039576609
		;
createNode transform -n "test_cage_anchor_6_handle_1_display_crv" -p "test_cage_anchor_6_handle_display";
	rename -uid "1414D297-468C-CA28-A56B-609D7D79FC2D";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape25" -p "test_cage_anchor_6_handle_1_display_crv";
	rename -uid "4FFED9B2-41BB-BEC2-00F4-38AB8E767DD0";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		7 0 7
		4.6666664392498474 0 7.0000002105699295
		;
createNode transform -n "test_cage_anchor_7_handle_display" -p "test_cage_display";
	rename -uid "0D973357-4E2D-DAB0-20BF-D99EDA05ECCD";
createNode transform -n "test_cage_anchor_7_handle_0_display_crv" -p "test_cage_anchor_7_handle_display";
	rename -uid "8FB762FE-49D6-D77E-0C3B-04B8CEF6EABE";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape26" -p "test_cage_anchor_7_handle_0_display_crv";
	rename -uid "7006DA6F-4779-0E5C-029D-E9AF3776E377";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 7
		2.3333331824980976 0 7.0000009529283833
		;
createNode transform -n "test_cage_anchor_7_handle_1_display_crv" -p "test_cage_anchor_7_handle_display";
	rename -uid "3A16555E-43C3-9855-B95A-64A66BED1C20";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape28" -p "test_cage_anchor_7_handle_1_display_crv";
	rename -uid "7CF71829-4877-2A5B-D7F9-61BE4659AA24";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 7
		-2.4659382630076931e-08 0 4.6666673031694783
		;
createNode transform -n "test_cage_anchor_7_handle_2_display_crv" -p "test_cage_anchor_7_handle_display";
	rename -uid "3AC90AC4-4D28-4D57-DF51-4FB8150322A2";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape31" -p "test_cage_anchor_7_handle_2_display_crv";
	rename -uid "9861FA72-41FD-CA80-D480-ADBB1884E924";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 7
		-2.3333333959499063 0 7.0000003367088386
		;
createNode transform -n "test_cage_anchor_8_handle_display" -p "test_cage_display";
	rename -uid "BAF220B6-4737-0F02-9979-CFA7BF297DBA";
createNode transform -n "test_cage_anchor_8_handle_0_display_crv" -p "test_cage_anchor_8_handle_display";
	rename -uid "93063871-4C09-953A-89F7-FFA7835F116E";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape32" -p "test_cage_anchor_8_handle_0_display_crv";
	rename -uid "42114CFF-4FBF-0E64-6969-EDA516E97281";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 7
		-4.6666662185767738 0 7.000000717466337
		;
createNode transform -n "test_cage_anchor_8_handle_1_display_crv" -p "test_cage_anchor_8_handle_display";
	rename -uid "F98B4AE5-4ADF-F5C0-826E-93998DC90AEC";
	setAttr ".ovdt" 2;
	setAttr ".ove" yes;
createNode nurbsCurve -n "curveShape34" -p "test_cage_anchor_8_handle_1_display_crv";
	rename -uid "7BB93C80-40FD-95B1-CDEB-DDB6999B44CE";
	setAttr -k off ".v";
	setAttr -s 2 ".cp";
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		-7 0 7
		-6.9999993982017994 0 4.6666670782768653
		;
createNode transform -n "test_cage_anchor_0" -p "test_cage";
	rename -uid "32BB320C-4E25-3318-D819-AB99A2B14436";
createNode transform -n "test_cage_anchor_0_null" -p "test_cage_anchor_0";
	rename -uid "2E5784F1-4C7A-9EB0-3777-A888F7BA2F97";
createNode transform -n "test_cage_anchor_0_srt" -p "test_cage_anchor_0_null";
	rename -uid "C8135A03-4E7C-D9BB-6515-42AF2E326185";
createNode transform -n "test_cage_anchor_0_ctl" -p "test_cage_anchor_0_srt";
	rename -uid "CDDE6568-4671-940A-FE9A-7E967D711968";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_0_ctl";
	rename -uid "1242700D-4E20-11CF-F8A1-DDBBA7C51DC4";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_0_handles" -p "test_cage_anchor_0";
	rename -uid "29677209-4CF1-6E79-068F-A99AB3C034E7";
createNode transform -n "test_cage_anchor_0_handle_0_null" -p "test_cage_anchor_0_handles";
	rename -uid "2600BA8B-4AE7-1B39-319F-CA969E667DF2";
createNode transform -n "test_cage_anchor_0_handle_0_srt" -p "test_cage_anchor_0_handle_0_null";
	rename -uid "FB3469C8-46FC-3DC0-9F62-74BD1F259544";
	setAttr ".t" -type "double3" 2.3333333653339716 0 5.3780633851863158e-07 ;
createNode transform -n "test_cage_anchor_0_handle_0_offset" -p "test_cage_anchor_0_handle_0_srt";
	rename -uid "ED11D66E-4A9E-551E-BB71-55B29EC6279D";
	setAttr ".rp" -type "double3" -2.3333333653339716 0 -5.3780633851863158e-07 ;
	setAttr ".sp" -type "double3" -2.3333333653339716 0 -5.3780633851863158e-07 ;
createNode transform -n "test_cage_anchor_0_handle_0_ctl" -p "test_cage_anchor_0_handle_0_offset";
	rename -uid "95C7CA9B-4E88-78DD-A016-55BF6E1C32BE";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_0_handle_0_ctl";
	rename -uid "327BAF21-4911-F7F5-8D56-BFA4DBFD7F02";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_0_handle_1_null" -p "test_cage_anchor_0_handles";
	rename -uid "0C9C3DE7-4477-4055-B97F-28990002DE54";
createNode transform -n "test_cage_anchor_0_handle_1_srt" -p "test_cage_anchor_0_handle_1_null";
	rename -uid "D3AF46B4-40C3-A721-5E6A-CAA7385E4D1D";
	setAttr ".t" -type "double3" -1.053041372796764e-07 0 -2.3333322621184527 ;
createNode transform -n "test_cage_anchor_0_handle_1_offset" -p "test_cage_anchor_0_handle_1_srt";
	rename -uid "D976ECBE-4D83-3FE6-9601-F7B9728F0524";
	setAttr ".rp" -type "double3" 1.053041372796764e-07 0 2.3333322621184527 ;
	setAttr ".sp" -type "double3" 1.053041372796764e-07 0 2.3333322621184527 ;
createNode transform -n "test_cage_anchor_0_handle_1_ctl" -p "test_cage_anchor_0_handle_1_offset";
	rename -uid "006A50F9-4514-F501-955C-E3AA7033251E";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_0_handle_1_ctl";
	rename -uid "2C5B6EF9-4A7B-E2BF-AD2A-B29AE3715688";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_0_handle_2_null" -p "test_cage_anchor_0_handles";
	rename -uid "3E9FF8FF-42A0-555E-BE03-A88F0428CAA1";
createNode transform -n "test_cage_anchor_0_handle_2_srt" -p "test_cage_anchor_0_handle_2_null";
	rename -uid "46B7B4F5-4651-58B4-E1A4-BBB9D341551C";
	setAttr ".t" -type "double3" -2.3333334568278854 0 5.3335950658817133e-07 ;
createNode transform -n "test_cage_anchor_0_handle_2_offset" -p "test_cage_anchor_0_handle_2_srt";
	rename -uid "2C8618FC-4030-3454-A556-409FB1F17211";
	setAttr ".rp" -type "double3" 2.3333334568278854 0 -5.3335950658817133e-07 ;
	setAttr ".sp" -type "double3" 2.3333334568278854 0 -5.3335950658817133e-07 ;
createNode transform -n "test_cage_anchor_0_handle_2_ctl" -p "test_cage_anchor_0_handle_2_offset";
	rename -uid "EA565A06-4C61-9BD1-AE52-079162CEAAD5";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_0_handle_2_ctl";
	rename -uid "4938D11B-4966-B87B-F715-AF93ADCA6B9F";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_0_handle_3_null" -p "test_cage_anchor_0_handles";
	rename -uid "CAC4C53A-4BED-DBB6-B572-04833540FC70";
createNode transform -n "test_cage_anchor_0_handle_3_srt" -p "test_cage_anchor_0_handle_3_null";
	rename -uid "61E38C80-4601-CA53-B98E-60AD207EF6E5";
	setAttr ".t" -type "double3" -3.1154839404292335e-08 0 2.33333391351945 ;
createNode transform -n "test_cage_anchor_0_handle_3_offset" -p "test_cage_anchor_0_handle_3_srt";
	rename -uid "08BFCD70-4C83-DD5F-9EEB-3AB9FC386644";
	setAttr ".rp" -type "double3" 3.1154839404292335e-08 0 -2.33333391351945 ;
	setAttr ".sp" -type "double3" 3.1154839404292335e-08 0 -2.33333391351945 ;
createNode transform -n "test_cage_anchor_0_handle_3_ctl" -p "test_cage_anchor_0_handle_3_offset";
	rename -uid "E86C87E2-482A-66BF-BE73-559066B2837D";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_0_handle_3_ctl";
	rename -uid "60EDC695-41F4-4E92-051D-5DAFFCDA8C23";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_1" -p "test_cage";
	rename -uid "97DBE0E6-433E-68F2-53C4-EAB0D0DF82B7";
createNode transform -n "test_cage_anchor_1_null" -p "test_cage_anchor_1";
	rename -uid "B84655D0-4944-6E60-CE25-8BB142DF8F82";
createNode transform -n "test_cage_anchor_1_srt" -p "test_cage_anchor_1_null";
	rename -uid "0150BFBD-460C-B52E-BA02-ED9BBD24AA61";
	setAttr ".t" -type "double3" 7 0 0 ;
createNode transform -n "test_cage_anchor_1_ctl" -p "test_cage_anchor_1_srt";
	rename -uid "82DA2790-40A8-C4CD-D9B7-1D9719DBD2FA";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_1_ctl";
	rename -uid "77451252-4971-8F77-19E8-87A935DC3C80";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_1_handles" -p "test_cage_anchor_1";
	rename -uid "79CCE500-4D31-94A5-573B-F8A3475C46C9";
	setAttr ".t" -type "double3" 7 0 0 ;
createNode transform -n "test_cage_anchor_1_handle_0_null" -p "test_cage_anchor_1_handles";
	rename -uid "D87ADADB-4AA5-BE88-9A3C-16B04AFF3A4B";
	setAttr ".t" -type "double3" -14 0 0 ;
createNode transform -n "test_cage_anchor_1_handle_0_srt" -p "test_cage_anchor_1_handle_0_null";
	rename -uid "42DD07B5-4E86-3632-30AB-E3B646CF78C8";
	setAttr ".t" -type "double3" 4.6666662773083312 0 1.0910754679877011e-06 ;
createNode transform -n "test_cage_anchor_1_handle_0_offset" -p "test_cage_anchor_1_handle_0_srt";
	rename -uid "0EA11D8C-415B-47B1-B28A-518C21F23891";
	setAttr ".rp" -type "double3" 2.3333337226916688 0 -1.0910754679877011e-06 ;
	setAttr ".sp" -type "double3" 2.3333337226916688 0 -1.0910754679877011e-06 ;
createNode transform -n "test_cage_anchor_1_handle_0_ctl" -p "test_cage_anchor_1_handle_0_offset";
	rename -uid "C5D48421-4448-55CF-BABB-7E9246C67CF6";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_1_handle_0_ctl";
	rename -uid "3C582401-4D51-F8EB-4655-FA95F6AF6F71";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_1_handle_1_null" -p "test_cage_anchor_1_handles";
	rename -uid "A303D466-4E97-83E5-A696-B5B1224C3321";
	setAttr ".t" -type "double3" -14 0 0 ;
createNode transform -n "test_cage_anchor_1_handle_1_srt" -p "test_cage_anchor_1_handle_1_null";
	rename -uid "9910792C-42A5-FE48-BC1A-B383173F19B6";
	setAttr ".t" -type "double3" 6.9999993322580369 0 -2.3333327688374745 ;
createNode transform -n "test_cage_anchor_1_handle_1_offset" -p "test_cage_anchor_1_handle_1_srt";
	rename -uid "F7005986-43C8-3FB4-8BF6-96881104B715";
	setAttr ".rp" -type "double3" 6.6774196305630085e-07 0 2.3333327688374745 ;
	setAttr ".sp" -type "double3" 6.6774196305630085e-07 0 2.3333327688374745 ;
createNode transform -n "test_cage_anchor_1_handle_1_ctl" -p "test_cage_anchor_1_handle_1_offset";
	rename -uid "462DE461-4EA9-9FB6-1CED-8B8923CFECD1";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_1_handle_1_ctl";
	rename -uid "D571E6D4-4323-2E1F-278A-4FAF66E73003";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_1_handle_2_null" -p "test_cage_anchor_1_handles";
	rename -uid "84E1AAD2-4BCD-6287-7769-A9B4F68767D3";
	setAttr ".t" -type "double3" -14 0 0 ;
createNode transform -n "test_cage_anchor_1_handle_2_srt" -p "test_cage_anchor_1_handle_2_null";
	rename -uid "5BC1910E-462B-DAC6-9D2F-67BD60BA477D";
	setAttr ".t" -type "double3" 6.9999991248986788 0 2.3333341869248376 ;
createNode transform -n "test_cage_anchor_1_handle_2_offset" -p "test_cage_anchor_1_handle_2_srt";
	rename -uid "5EA4BBD6-4D25-9716-D02B-CBB7CA06AC2D";
	setAttr ".rp" -type "double3" 8.7510132118495676e-07 0 -2.3333341869248376 ;
	setAttr ".sp" -type "double3" 8.7510132118495676e-07 0 -2.3333341869248376 ;
createNode transform -n "test_cage_anchor_1_handle_2_ctl" -p "test_cage_anchor_1_handle_2_offset";
	rename -uid "B8F8A141-4BDA-AC3A-AB39-59818D211C85";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_1_handle_2_ctl";
	rename -uid "904AB812-47D2-FC92-6089-FD9D0A81FE87";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_2" -p "test_cage";
	rename -uid "05527887-4CD0-44C7-7E1E-9BBD1FCB1866";
createNode transform -n "test_cage_anchor_2_null" -p "test_cage_anchor_2";
	rename -uid "7DDE4CC2-444D-E938-4483-E4849D350328";
createNode transform -n "test_cage_anchor_2_srt" -p "test_cage_anchor_2_null";
	rename -uid "D5F12AC4-471B-383B-B313-BEAA55007C50";
	setAttr ".t" -type "double3" 7 0 -7 ;
createNode transform -n "test_cage_anchor_2_ctl" -p "test_cage_anchor_2_srt";
	rename -uid "4080F7B6-42E8-0D4E-62C8-5DA417E650C3";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_2_ctl";
	rename -uid "3661A84A-49C9-5021-5347-CD87FB93E301";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_2_handles" -p "test_cage_anchor_2";
	rename -uid "10243704-4236-798A-B2EA-E3B3F4A5E51C";
	setAttr ".t" -type "double3" 7 0 -7 ;
createNode transform -n "test_cage_anchor_2_handle_0_null" -p "test_cage_anchor_2_handles";
	rename -uid "A5383518-40AE-289E-9BDD-BCAF5118227B";
	setAttr ".t" -type "double3" -14 0 14 ;
createNode transform -n "test_cage_anchor_2_handle_0_srt" -p "test_cage_anchor_2_handle_0_null";
	rename -uid "7DDCC0D5-4F68-83C8-F833-43B050ADC327";
	setAttr ".t" -type "double3" 6.9999995699620889 0 -4.6666648508466322 ;
createNode transform -n "test_cage_anchor_2_handle_0_offset" -p "test_cage_anchor_2_handle_0_srt";
	rename -uid "A66496F2-4890-6CAD-EAEB-C1824E3A7E3A";
	setAttr ".rp" -type "double3" 4.3003791105888922e-07 0 -2.3333351491533678 ;
	setAttr ".sp" -type "double3" 4.3003791105888922e-07 0 -2.3333351491533678 ;
createNode transform -n "test_cage_anchor_2_handle_0_ctl" -p "test_cage_anchor_2_handle_0_offset";
	rename -uid "DD810D86-422E-4847-0881-62B8BCC110B3";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_2_handle_0_ctl";
	rename -uid "D709B2F1-4804-0D4E-B522-3280220016EF";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_2_handle_1_null" -p "test_cage_anchor_2_handles";
	rename -uid "3FA503F2-4ADE-255F-D08C-4AB0E392C5DA";
	setAttr ".t" -type "double3" -14 0 14 ;
createNode transform -n "test_cage_anchor_2_handle_1_srt" -p "test_cage_anchor_2_handle_1_null";
	rename -uid "5704F641-4BAB-AEFF-74E5-F9AFFBBB0DC7";
	setAttr ".t" -type "double3" 4.6666666344585144 0 -6.9999999932443462 ;
createNode transform -n "test_cage_anchor_2_handle_1_offset" -p "test_cage_anchor_2_handle_1_srt";
	rename -uid "431AF8D3-4B4E-0C71-C5DC-44BB975ED8A2";
	setAttr ".rp" -type "double3" 2.3333333655414856 0 -6.7556538141388955e-09 ;
	setAttr ".sp" -type "double3" 2.3333333655414856 0 -6.7556538141388955e-09 ;
createNode transform -n "test_cage_anchor_2_handle_1_ctl" -p "test_cage_anchor_2_handle_1_offset";
	rename -uid "42A25DA2-4AC7-A96C-2153-DF8D794C912E";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_2_handle_1_ctl";
	rename -uid "AC387FC1-4A61-6E94-145F-83B1F1FFAAFF";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_3" -p "test_cage";
	rename -uid "500DC916-42AF-6A3E-C021-17962FB313A7";
createNode transform -n "test_cage_anchor_3_null" -p "test_cage_anchor_3";
	rename -uid "2AE85D9F-4A7B-0337-1867-418DBCDD9CCF";
createNode transform -n "test_cage_anchor_3_srt" -p "test_cage_anchor_3_null";
	rename -uid "08922CA2-4909-1340-A9F3-278A6C74ED76";
	setAttr ".t" -type "double3" 0 0 -7 ;
createNode transform -n "test_cage_anchor_3_ctl" -p "test_cage_anchor_3_srt";
	rename -uid "F89B4E61-46AB-AF90-90A0-7083585048E8";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_3_ctl";
	rename -uid "A1767006-43F5-56C3-5255-099256705D98";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_3_handles" -p "test_cage_anchor_3";
	rename -uid "6B3C6C93-4DC7-6AD2-271C-6FB94B63ACED";
	setAttr ".t" -type "double3" 0 0 -7 ;
createNode transform -n "test_cage_anchor_3_handle_0_null" -p "test_cage_anchor_3_handles";
	rename -uid "285E7DC4-4B4C-A43A-A698-0BA80BB936A1";
	setAttr ".t" -type "double3" 0 0 14 ;
createNode transform -n "test_cage_anchor_3_handle_0_srt" -p "test_cage_anchor_3_handle_0_null";
	rename -uid "868FB80D-40DE-0D05-0AB4-E9BA533B140D";
	setAttr ".t" -type "double3" 2.3333333588809921 0 -6.9999999932443515 ;
createNode transform -n "test_cage_anchor_3_handle_0_offset" -p "test_cage_anchor_3_handle_0_srt";
	rename -uid "4DF60AD5-4A68-897A-4B79-F48F6BA7257F";
	setAttr ".rp" -type "double3" -2.3333333588809921 0 -6.7556484850683773e-09 ;
	setAttr ".sp" -type "double3" -2.3333333588809921 0 -6.7556484850683773e-09 ;
createNode transform -n "test_cage_anchor_3_handle_0_ctl" -p "test_cage_anchor_3_handle_0_offset";
	rename -uid "41F4065F-49BD-B69B-D3EE-749FC8E69B2C";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_3_handle_0_ctl";
	rename -uid "C6DCCA39-4822-0661-FF82-CBAD73596B6B";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_3_handle_1_null" -p "test_cage_anchor_3_handles";
	rename -uid "349A555E-4FCE-DCB5-E457-D592F797A3BA";
	setAttr ".t" -type "double3" 0 0 14 ;
createNode transform -n "test_cage_anchor_3_handle_1_srt" -p "test_cage_anchor_3_handle_1_null";
	rename -uid "957A1269-47E3-3E39-18F5-7B9A536B9DC3";
	setAttr ".t" -type "double3" 1.2575157539212984e-08 0 -4.6666661455102991 ;
createNode transform -n "test_cage_anchor_3_handle_1_offset" -p "test_cage_anchor_3_handle_1_srt";
	rename -uid "9B598335-47D7-0AE2-5545-CC97EBF1A64A";
	setAttr ".rp" -type "double3" -1.2575157539212984e-08 0 -2.3333338544897009 ;
	setAttr ".sp" -type "double3" -1.2575157539212984e-08 0 -2.3333338544897009 ;
createNode transform -n "test_cage_anchor_3_handle_1_ctl" -p "test_cage_anchor_3_handle_1_offset";
	rename -uid "DBAF43F3-42AD-0C7C-AD11-F494388109AD";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_3_handle_1_ctl";
	rename -uid "45BDF78B-48BB-0CFA-0D7A-31BE8C7CAABD";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_3_handle_2_null" -p "test_cage_anchor_3_handles";
	rename -uid "7859EBC5-4528-E2D0-481E-8CA0FBD02C0A";
	setAttr ".t" -type "double3" 0 0 14 ;
createNode transform -n "test_cage_anchor_3_handle_2_srt" -p "test_cage_anchor_3_handle_2_null";
	rename -uid "34EB6C19-427B-8266-FCBF-4DAD304242AA";
	setAttr ".t" -type "double3" -2.3333333588809921 0 -6.9999999932443515 ;
createNode transform -n "test_cage_anchor_3_handle_2_offset" -p "test_cage_anchor_3_handle_2_srt";
	rename -uid "821C1745-4D83-8E51-8B5D-F7A5F49E6FC9";
	setAttr ".rp" -type "double3" 2.3333333588809921 0 -6.7556484850683773e-09 ;
	setAttr ".sp" -type "double3" 2.3333333588809921 0 -6.7556484850683773e-09 ;
createNode transform -n "test_cage_anchor_3_handle_2_ctl" -p "test_cage_anchor_3_handle_2_offset";
	rename -uid "7D2FC73B-445D-36F3-4B2A-55A184C817C7";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_3_handle_2_ctl";
	rename -uid "523636BB-428E-5850-121F-23AEF871D9C7";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_4" -p "test_cage";
	rename -uid "EF670435-4307-8F31-7FE6-458BCAEBEF92";
createNode transform -n "test_cage_anchor_4_null" -p "test_cage_anchor_4";
	rename -uid "15BE7D14-49E5-3681-54E1-BCB1DE334B9F";
createNode transform -n "test_cage_anchor_4_srt" -p "test_cage_anchor_4_null";
	rename -uid "0EC07BAF-4CD4-C400-395E-928772C9B72C";
	setAttr ".t" -type "double3" -7 0 0 ;
createNode transform -n "test_cage_anchor_4_ctl" -p "test_cage_anchor_4_srt";
	rename -uid "E894CD49-4BD3-9214-F23B-FBAB1FB19A86";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_4_ctl";
	rename -uid "626A72A3-4F91-E132-0DF1-3894B3BE4506";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_4_handles" -p "test_cage_anchor_4";
	rename -uid "A639AC37-42BB-544A-9ABE-DD8A84CF41C6";
	setAttr ".t" -type "double3" -7 0 0 ;
createNode transform -n "test_cage_anchor_4_handle_0_null" -p "test_cage_anchor_4_handles";
	rename -uid "FE135D13-4A3F-4C56-00F0-168FF6174902";
	setAttr ".t" -type "double3" 14 0 0 ;
createNode transform -n "test_cage_anchor_4_handle_0_srt" -p "test_cage_anchor_4_handle_0_null";
	rename -uid "CE7A8B5E-49B6-EF21-1EA7-AC9B57828B01";
	setAttr ".t" -type "double3" -4.6666661391802515 0 1.4535012517191692e-06 ;
createNode transform -n "test_cage_anchor_4_handle_0_offset" -p "test_cage_anchor_4_handle_0_srt";
	rename -uid "0A67BEA4-4EB0-BE63-03C2-5094EC976AD6";
	setAttr ".rp" -type "double3" -2.3333338608197485 0 -1.4535012517191692e-06 ;
	setAttr ".sp" -type "double3" -2.3333338608197485 0 -1.4535012517191692e-06 ;
createNode transform -n "test_cage_anchor_4_handle_0_ctl" -p "test_cage_anchor_4_handle_0_offset";
	rename -uid "69F59A6D-4F84-2C11-C15A-29AA50372874";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_4_handle_0_ctl";
	rename -uid "D317BB36-42B3-34D2-EE88-59B79197F2A3";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_4_handle_1_null" -p "test_cage_anchor_4_handles";
	rename -uid "9515E529-4AC7-3C16-E6B9-CABFE1AE96CB";
	setAttr ".t" -type "double3" 14 0 0 ;
createNode transform -n "test_cage_anchor_4_handle_1_srt" -p "test_cage_anchor_4_handle_1_null";
	rename -uid "815C604A-413B-D843-7550-EF94976D0840";
	setAttr ".t" -type "double3" -6.9999996457418678 0 -2.3333320200869738 ;
createNode transform -n "test_cage_anchor_4_handle_1_offset" -p "test_cage_anchor_4_handle_1_srt";
	rename -uid "2CD9CC88-4852-DD85-277A-579F74FE2446";
	setAttr ".rp" -type "double3" -3.5425813216249935e-07 0 2.3333320200869738 ;
	setAttr ".sp" -type "double3" -3.5425813216249935e-07 0 2.3333320200869738 ;
createNode transform -n "test_cage_anchor_4_handle_1_ctl" -p "test_cage_anchor_4_handle_1_offset";
	rename -uid "CED1885B-4435-BF7D-93AE-B9ACBD1D39F2";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_4_handle_1_ctl";
	rename -uid "C8C0C93B-44F2-2519-AFDE-498D259D568C";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_4_handle_2_null" -p "test_cage_anchor_4_handles";
	rename -uid "C9C0A027-43FE-B675-88AC-35963976070C";
	setAttr ".t" -type "double3" 14 0 0 ;
createNode transform -n "test_cage_anchor_4_handle_2_srt" -p "test_cage_anchor_4_handle_2_null";
	rename -uid "334DCA33-4E58-B00B-3F49-F28A75C83B8E";
	setAttr ".t" -type "double3" -6.9999998722726584 0 2.3333342709237779 ;
createNode transform -n "test_cage_anchor_4_handle_2_offset" -p "test_cage_anchor_4_handle_2_srt";
	rename -uid "12BE4DCF-467B-01B6-5550-E1A1311D88A7";
	setAttr ".rp" -type "double3" -1.2772734159227639e-07 0 -2.3333342709237779 ;
	setAttr ".sp" -type "double3" -1.2772734159227639e-07 0 -2.3333342709237779 ;
createNode transform -n "test_cage_anchor_4_handle_2_ctl" -p "test_cage_anchor_4_handle_2_offset";
	rename -uid "CE3EB948-47D8-F172-F1B4-BFBCA5F5E4C7";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_4_handle_2_ctl";
	rename -uid "B6182C72-47EA-E090-2DA9-DA97FD4FDCF8";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_5" -p "test_cage";
	rename -uid "AC5B7949-401B-12D5-762C-0DA5172515E2";
createNode transform -n "test_cage_anchor_5_null" -p "test_cage_anchor_5";
	rename -uid "BB0C2518-4265-0CDF-A4B3-C290CC259951";
createNode transform -n "test_cage_anchor_5_srt" -p "test_cage_anchor_5_null";
	rename -uid "1894E704-4565-009E-6C57-ED9078230725";
	setAttr ".t" -type "double3" -7 0 -7 ;
createNode transform -n "test_cage_anchor_5_ctl" -p "test_cage_anchor_5_srt";
	rename -uid "DBA336F9-465F-925F-E5CE-12ACF3789875";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_5_ctl";
	rename -uid "0BEC563A-4A00-07C8-8AFE-5D91B52D1D49";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_5_handles" -p "test_cage_anchor_5";
	rename -uid "8336ECDB-4857-05FA-9C96-A595D1E10D53";
	setAttr ".t" -type "double3" -7 0 -7 ;
createNode transform -n "test_cage_anchor_5_handle_0_null" -p "test_cage_anchor_5_handles";
	rename -uid "59D9F299-479D-D87F-80A0-F382FA06A261";
	setAttr ".t" -type "double3" 14 0 14 ;
createNode transform -n "test_cage_anchor_5_handle_0_srt" -p "test_cage_anchor_5_handle_0_null";
	rename -uid "BB8FAEB0-472D-922D-CB6E-2CAE53B7A3A7";
	setAttr ".t" -type "double3" -6.9999995979861156 0 -4.6666656863033431 ;
createNode transform -n "test_cage_anchor_5_handle_0_offset" -p "test_cage_anchor_5_handle_0_srt";
	rename -uid "D364FD47-49CE-D490-7589-948F68B66B27";
	setAttr ".rp" -type "double3" -4.0201388440408437e-07 0 -2.3333343136966569 ;
	setAttr ".sp" -type "double3" -4.0201388440408437e-07 0 -2.3333343136966569 ;
createNode transform -n "test_cage_anchor_5_handle_0_ctl" -p "test_cage_anchor_5_handle_0_offset";
	rename -uid "57FFFDED-4912-D9EB-A660-F787EBEB8003";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_5_handle_0_ctl";
	rename -uid "B708C032-49F2-59D9-36F5-D69F11D9E836";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_5_handle_1_null" -p "test_cage_anchor_5_handles";
	rename -uid "93054E65-461B-6296-53F1-67BD3F24AA51";
	setAttr ".t" -type "double3" 14 0 14 ;
createNode transform -n "test_cage_anchor_5_handle_1_srt" -p "test_cage_anchor_5_handle_1_null";
	rename -uid "AC9498DF-4616-685C-D909-5EAE01F261FD";
	setAttr ".t" -type "double3" -4.6666666344585144 0 -6.9999999932443462 ;
createNode transform -n "test_cage_anchor_5_handle_1_offset" -p "test_cage_anchor_5_handle_1_srt";
	rename -uid "7D293CF2-4656-59B7-2CE8-FCB733A22490";
	setAttr ".rp" -type "double3" -2.3333333655414856 0 -6.7556538141388955e-09 ;
	setAttr ".sp" -type "double3" -2.3333333655414856 0 -6.7556538141388955e-09 ;
createNode transform -n "test_cage_anchor_5_handle_1_ctl" -p "test_cage_anchor_5_handle_1_offset";
	rename -uid "B8C42B10-4E3A-EA1B-0152-D995498F32F0";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_5_handle_1_ctl";
	rename -uid "1AC8ECA0-4376-0F52-071B-E1A48C7670BA";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_6" -p "test_cage";
	rename -uid "6D309EB1-4D79-A34D-F29E-E7AC3C87201C";
createNode transform -n "test_cage_anchor_6_null" -p "test_cage_anchor_6";
	rename -uid "F1CD9C6F-4FF8-D8B0-ECC3-AF84897A20A9";
createNode transform -n "test_cage_anchor_6_srt" -p "test_cage_anchor_6_null";
	rename -uid "90393D21-4A51-20D5-8ECC-568CEEE23E2E";
	setAttr ".t" -type "double3" 7 0 7 ;
createNode transform -n "test_cage_anchor_6_ctl" -p "test_cage_anchor_6_srt";
	rename -uid "115A43D6-478E-FE58-1311-C98A0603680F";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_6_ctl";
	rename -uid "F342146A-4C9A-492D-A7DC-43813238D70B";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_6_handles" -p "test_cage_anchor_6";
	rename -uid "10F11C23-4340-2D93-7F41-A69218C2A51B";
	setAttr ".t" -type "double3" 7 0 7 ;
createNode transform -n "test_cage_anchor_6_handle_0_null" -p "test_cage_anchor_6_handles";
	rename -uid "8FC701D9-4E53-F58C-B450-ADA9CAFA9140";
	setAttr ".t" -type "double3" -14 0 -14 ;
createNode transform -n "test_cage_anchor_6_handle_0_srt" -p "test_cage_anchor_6_handle_0_null";
	rename -uid "DEAB5525-4735-EA3D-5396-988DD45E9DEC";
	setAttr ".t" -type "double3" 6.9999996322473912 0 4.6666669039576609 ;
createNode transform -n "test_cage_anchor_6_handle_0_offset" -p "test_cage_anchor_6_handle_0_srt";
	rename -uid "A74A8C20-4FDF-478B-FE2D-B280EDB5A19E";
	setAttr ".rp" -type "double3" 3.6775260880972382e-07 0 2.3333330960423391 ;
	setAttr ".sp" -type "double3" 3.6775260880972382e-07 0 2.3333330960423391 ;
createNode transform -n "test_cage_anchor_6_handle_0_ctl" -p "test_cage_anchor_6_handle_0_offset";
	rename -uid "10DBA5E8-4856-8EA9-22EE-1CBE5F7583CA";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_6_handle_0_ctl";
	rename -uid "11248B2C-4BD5-70CB-DE67-D583ACBBDA35";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_6_handle_1_null" -p "test_cage_anchor_6_handles";
	rename -uid "BCD0E1EF-4BCF-AD6D-53A0-6FA30E8433F0";
	setAttr ".t" -type "double3" -14 0 -14 ;
createNode transform -n "test_cage_anchor_6_handle_1_srt" -p "test_cage_anchor_6_handle_1_null";
	rename -uid "06E0643B-4B09-960E-B4BE-45B2DF193C8D";
	setAttr ".t" -type "double3" 4.6666664392498474 0 7.0000002105699295 ;
createNode transform -n "test_cage_anchor_6_handle_1_offset" -p "test_cage_anchor_6_handle_1_srt";
	rename -uid "F70D49F8-432F-7AAB-9682-FD8ADCFDE0B9";
	setAttr ".rp" -type "double3" 2.3333335607501526 0 -2.1056992949297637e-07 ;
	setAttr ".sp" -type "double3" 2.3333335607501526 0 -2.1056992949297637e-07 ;
createNode transform -n "test_cage_anchor_6_handle_1_ctl" -p "test_cage_anchor_6_handle_1_offset";
	rename -uid "AA57DAF3-4970-C1DC-A5FF-CD853C1AC5FF";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_6_handle_1_ctl";
	rename -uid "B002F121-4D92-4F11-BC39-0297641F6979";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_7" -p "test_cage";
	rename -uid "A667BC27-4146-DCF9-9FBB-9E8BC906FBA2";
createNode transform -n "test_cage_anchor_7_null" -p "test_cage_anchor_7";
	rename -uid "CCC45539-490B-9214-1BD2-689141B543D0";
createNode transform -n "test_cage_anchor_7_srt" -p "test_cage_anchor_7_null";
	rename -uid "1B539471-4AD7-A4EC-80EA-EC8F7625A353";
	setAttr ".t" -type "double3" 0 0 7 ;
createNode transform -n "test_cage_anchor_7_ctl" -p "test_cage_anchor_7_srt";
	rename -uid "EF0AAB0A-4186-D0AF-FF08-31930441507D";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_7_ctl";
	rename -uid "606BB3FA-419C-8749-0C9B-FD81266EAAAA";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_7_handles" -p "test_cage_anchor_7";
	rename -uid "71DD1821-422D-3C7E-A154-93BAC5341371";
	setAttr ".t" -type "double3" 0 0 7 ;
createNode transform -n "test_cage_anchor_7_handle_0_null" -p "test_cage_anchor_7_handles";
	rename -uid "AA6A9534-4925-1FB8-B7BD-B7975194E35F";
	setAttr ".t" -type "double3" 0 0 -14 ;
createNode transform -n "test_cage_anchor_7_handle_0_srt" -p "test_cage_anchor_7_handle_0_null";
	rename -uid "5BB1BDD5-4600-FA4D-7D71-66AF67D4EA90";
	setAttr ".t" -type "double3" 2.3333331824980976 0 7.0000009529283833 ;
createNode transform -n "test_cage_anchor_7_handle_0_offset" -p "test_cage_anchor_7_handle_0_srt";
	rename -uid "0DFE7E44-448B-873E-7011-ADB970B4E896";
	setAttr ".rp" -type "double3" -2.3333331824980976 0 -9.5292838331317853e-07 ;
	setAttr ".sp" -type "double3" -2.3333331824980976 0 -9.5292838331317853e-07 ;
createNode transform -n "test_cage_anchor_7_handle_0_ctl" -p "test_cage_anchor_7_handle_0_offset";
	rename -uid "DF04752E-4096-7DC1-7294-65B902F4916C";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_7_handle_0_ctl";
	rename -uid "EE3505D9-44BC-A065-5362-2FB97511187E";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_7_handle_1_null" -p "test_cage_anchor_7_handles";
	rename -uid "D88A07BC-41B3-88CD-BFAC-A69B8B29AF45";
	setAttr ".t" -type "double3" 0 0 -14 ;
createNode transform -n "test_cage_anchor_7_handle_1_srt" -p "test_cage_anchor_7_handle_1_null";
	rename -uid "1444AAE9-4C69-9E9B-A6A4-00850714326B";
	setAttr ".t" -type "double3" -2.4659382630076931e-08 0 4.6666673031694783 ;
createNode transform -n "test_cage_anchor_7_handle_1_offset" -p "test_cage_anchor_7_handle_1_srt";
	rename -uid "1160DD8F-499C-9186-EE01-6DACF7E4C1F5";
	setAttr ".rp" -type "double3" 2.4659382630076931e-08 0 2.3333326968305217 ;
	setAttr ".sp" -type "double3" 2.4659382630076931e-08 0 2.3333326968305217 ;
createNode transform -n "test_cage_anchor_7_handle_1_ctl" -p "test_cage_anchor_7_handle_1_offset";
	rename -uid "C6AF8B7D-4A71-EA8C-94E9-E4A748F0CB93";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_7_handle_1_ctl";
	rename -uid "00D5F649-4103-A890-D02B-66B01B17059A";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_7_handle_2_null" -p "test_cage_anchor_7_handles";
	rename -uid "886C61FD-4773-A759-2789-448F2C2BA142";
	setAttr ".t" -type "double3" 0 0 -14 ;
createNode transform -n "test_cage_anchor_7_handle_2_srt" -p "test_cage_anchor_7_handle_2_null";
	rename -uid "F0050B90-4674-3EF0-87B3-AA9E594F6526";
	setAttr ".t" -type "double3" -2.3333333959499063 0 7.0000003367088386 ;
createNode transform -n "test_cage_anchor_7_handle_2_offset" -p "test_cage_anchor_7_handle_2_srt";
	rename -uid "E7873027-44FD-1F86-DB73-58B0ACF98E58";
	setAttr ".rp" -type "double3" 2.3333333959499063 0 -3.3670883858860634e-07 ;
	setAttr ".sp" -type "double3" 2.3333333959499063 0 -3.3670883858860634e-07 ;
createNode transform -n "test_cage_anchor_7_handle_2_ctl" -p "test_cage_anchor_7_handle_2_offset";
	rename -uid "0EE94D7C-4EAC-6152-1E8A-D0BDC80E1384";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_7_handle_2_ctl";
	rename -uid "EFD97221-4D4B-5D95-A68B-1994B3C848AE";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_8" -p "test_cage";
	rename -uid "E4602288-4556-20B0-42DB-AD93BF328B66";
createNode transform -n "test_cage_anchor_8_null" -p "test_cage_anchor_8";
	rename -uid "4796755A-4077-DAB2-9354-929E84A099C7";
createNode transform -n "test_cage_anchor_8_srt" -p "test_cage_anchor_8_null";
	rename -uid "FA2BD7E5-4FE5-D674-D412-4B819617D3DA";
	setAttr ".t" -type "double3" -7 0 7 ;
createNode transform -n "test_cage_anchor_8_ctl" -p "test_cage_anchor_8_srt";
	rename -uid "C2C886CB-437B-13C7-F8D2-17B89C049E78";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_8_ctl";
	rename -uid "EAD62917-4926-4C81-DE9F-E7A3033C45E0";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.74400002 0 0.86699998 ;
	setAttr ".ls" 3;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 -0.20000000000000001
		-0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 0.20000000000000001
		0.20000000000000001 0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 0.20000000000000001
		-0.20000000000000001 -0.20000000000000001 -0.20000000000000001
		;
createNode transform -n "test_cage_anchor_8_handles" -p "test_cage_anchor_8";
	rename -uid "FA5194BF-48A8-AACD-5907-07AA5204F916";
	setAttr ".t" -type "double3" -7 0 7 ;
createNode transform -n "test_cage_anchor_8_handle_0_null" -p "test_cage_anchor_8_handles";
	rename -uid "FE43E520-4531-7E11-EC7D-EC8C77A51C05";
	setAttr ".t" -type "double3" 14 0 -14 ;
createNode transform -n "test_cage_anchor_8_handle_0_srt" -p "test_cage_anchor_8_handle_0_null";
	rename -uid "C1BD2BD6-4EF5-A8F5-B87B-5A9E11A7C609";
	setAttr ".t" -type "double3" -4.6666662185767738 0 7.000000717466337 ;
createNode transform -n "test_cage_anchor_8_handle_0_offset" -p "test_cage_anchor_8_handle_0_srt";
	rename -uid "DFC29B96-4C1D-E439-0073-54A29266B74B";
	setAttr ".rp" -type "double3" -2.3333337814232262 0 -7.1746633700797702e-07 ;
	setAttr ".sp" -type "double3" -2.3333337814232262 0 -7.1746633700797702e-07 ;
createNode transform -n "test_cage_anchor_8_handle_0_ctl" -p "test_cage_anchor_8_handle_0_offset";
	rename -uid "5840CE27-4C25-6596-D57F-669C96095A05";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_8_handle_0_ctl";
	rename -uid "294262D7-40C8-68EC-9CE9-F088788709B7";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode transform -n "test_cage_anchor_8_handle_1_null" -p "test_cage_anchor_8_handles";
	rename -uid "D980A2E1-43E4-DCB8-572E-A2A47BD58293";
	setAttr ".t" -type "double3" 14 0 -14 ;
createNode transform -n "test_cage_anchor_8_handle_1_srt" -p "test_cage_anchor_8_handle_1_null";
	rename -uid "17EA0DC8-4B97-B502-D07C-CD977CDF7023";
	setAttr ".t" -type "double3" -6.9999993982017994 0 4.6666670782768653 ;
createNode transform -n "test_cage_anchor_8_handle_1_offset" -p "test_cage_anchor_8_handle_1_srt";
	rename -uid "E60F4E77-4619-FD28-BB3E-8CBDA62174E1";
	setAttr ".rp" -type "double3" -6.0179820060568545e-07 0 2.3333329217231347 ;
	setAttr ".sp" -type "double3" -6.0179820060568545e-07 0 2.3333329217231347 ;
createNode transform -n "test_cage_anchor_8_handle_1_ctl" -p "test_cage_anchor_8_handle_1_offset";
	rename -uid "4DF2304E-4A11-885E-4656-A2802D801F1A";
	setAttr -l on -k off ".rx";
	setAttr -l on -k off ".ry";
	setAttr -l on -k off ".rz";
	setAttr -l on -k off ".sx";
	setAttr -l on -k off ".sy";
	setAttr -l on -k off ".sz";
createNode nurbsCurve -n "boxShape" -p "test_cage_anchor_8_handle_1_ctl";
	rename -uid "868AB3BC-4AB8-F492-CA31-2F984EE4C918";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovrgbf" yes;
	setAttr ".ovrgb" -type "float3" 0.36399999 0.014 1 ;
	setAttr ".ls" 1.5;
	setAttr ".cc" -type "nurbsCurve" 
		1 15 0 no 3
		16 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		16
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 -0.10000000000000001
		-0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 0.10000000000000001
		0.10000000000000001 0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 0.10000000000000001
		-0.10000000000000001 -0.10000000000000001 -0.10000000000000001
		;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "20C7D986-474E-5D70-98FC-EBBE3813B461";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "7CECEA62-41A5-8900-D17B-5697BE8EEAD9";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "3D5F6297-458C-EB52-2ACF-7D8606DB021D";
createNode displayLayerManager -n "layerManager";
	rename -uid "030E7E46-4CC6-61E3-B38A-CD8CCA31DDE9";
createNode displayLayer -n "defaultLayer";
	rename -uid "B56A453B-403A-3851-EF4A-7699E4AB686C";
	setAttr ".ufem" -type "stringArray" 0  ;
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "1662CBF6-4C51-0D62-1528-4E9E1B272288";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "91D79A9A-4E51-2BC9-AB33-378B80C3FFB6";
	setAttr ".g" yes;
createNode decomposeMatrix -n "test_cage_anchor_0_ctl_dcmp";
	rename -uid "80F110D3-4A00-229C-B7C3-7DB7966B20EE";
createNode decomposeMatrix -n "test_cage_anchor_0_handle_0_ctl_dcmp";
	rename -uid "0CF8E85A-43D1-0352-A6F2-9F89690764A8";
createNode decomposeMatrix -n "test_cage_anchor_1_ctl_dcmp";
	rename -uid "3DAB09BB-4CEF-7506-A839-14B77A487214";
createNode decomposeMatrix -n "test_cage_anchor_1_handle_0_ctl_dcmp";
	rename -uid "CBDC7E77-414C-F752-63DB-B2BBC72F9C88";
createNode decomposeMatrix -n "test_cage_anchor_1_handle_1_ctl_dcmp";
	rename -uid "BFA3AEF7-42CE-717F-A699-839E9A1525CE";
createNode decomposeMatrix -n "test_cage_anchor_2_ctl_dcmp";
	rename -uid "523054A9-4ECC-05AB-C497-81B504D24A10";
createNode decomposeMatrix -n "test_cage_anchor_2_handle_0_ctl_dcmp";
	rename -uid "9995622C-4ED8-D108-EA83-6BAFE72B73BD";
createNode decomposeMatrix -n "test_cage_anchor_2_handle_1_ctl_dcmp";
	rename -uid "620440B2-4EE3-397B-8E0A-D5804F328329";
createNode decomposeMatrix -n "test_cage_anchor_3_ctl_dcmp";
	rename -uid "CB81A99D-4818-54F7-4A43-0DA21E48CB91";
createNode decomposeMatrix -n "test_cage_anchor_3_handle_0_ctl_dcmp";
	rename -uid "0C58B4E5-4AA3-3010-B195-15AAC1AC3821";
createNode decomposeMatrix -n "test_cage_anchor_3_handle_1_ctl_dcmp";
	rename -uid "1B653B19-4F6C-B290-18F3-65A1406586D5";
createNode decomposeMatrix -n "test_cage_anchor_0_handle_1_ctl_dcmp";
	rename -uid "B8AB3BD4-49E1-3DA9-C36F-0DB752F2C38F";
createNode decomposeMatrix -n "test_cage_anchor_0_handle_2_ctl_dcmp";
	rename -uid "220C0299-47C5-A013-7FEA-3991372D7F37";
createNode decomposeMatrix -n "test_cage_anchor_4_ctl_dcmp";
	rename -uid "D4298918-4891-7E69-3DC9-E1AE43AF4BB6";
createNode decomposeMatrix -n "test_cage_anchor_4_handle_0_ctl_dcmp";
	rename -uid "D936837A-478A-308C-5EA6-F39B711FAFE4";
createNode decomposeMatrix -n "test_cage_anchor_4_handle_1_ctl_dcmp";
	rename -uid "FB915806-4106-5E5E-DC5B-4C8935CF7152";
createNode decomposeMatrix -n "test_cage_anchor_5_ctl_dcmp";
	rename -uid "57ECF7D0-4035-0EBC-7D32-9C9CC1A3D92E";
createNode decomposeMatrix -n "test_cage_anchor_5_handle_0_ctl_dcmp";
	rename -uid "3390FCD1-4EA2-DD31-55A9-5CBE860FC556";
createNode decomposeMatrix -n "test_cage_anchor_5_handle_1_ctl_dcmp";
	rename -uid "4FC599E1-4716-5749-ADDB-2DBBAF231B2E";
createNode decomposeMatrix -n "test_cage_anchor_3_handle_2_ctl_dcmp";
	rename -uid "588BADF7-4250-A17A-8F7F-9CB1AC0A34B2";
createNode decomposeMatrix -n "test_cage_anchor_1_handle_2_ctl_dcmp";
	rename -uid "F19021E2-4BFF-C34B-8B1D-928DB7A59858";
createNode decomposeMatrix -n "test_cage_anchor_6_ctl_dcmp";
	rename -uid "5ABEC34A-417D-5341-44E5-CE8A3463E74E";
createNode decomposeMatrix -n "test_cage_anchor_6_handle_0_ctl_dcmp";
	rename -uid "0ADC7EEF-4E48-CFC0-60F9-76B53287DEBD";
createNode decomposeMatrix -n "test_cage_anchor_6_handle_1_ctl_dcmp";
	rename -uid "3430C356-486F-F9C8-80F5-809EA0B05061";
createNode decomposeMatrix -n "test_cage_anchor_7_ctl_dcmp";
	rename -uid "2691ED44-464F-0C59-FE02-359396E18DBB";
createNode decomposeMatrix -n "test_cage_anchor_7_handle_0_ctl_dcmp";
	rename -uid "48ED69B3-4FC6-581B-E347-70A77CBF6FC1";
createNode decomposeMatrix -n "test_cage_anchor_7_handle_1_ctl_dcmp";
	rename -uid "9639FE69-4AF9-4591-3A15-4AAA70B7640A";
createNode decomposeMatrix -n "test_cage_anchor_0_handle_3_ctl_dcmp";
	rename -uid "81D54EEF-4068-FECE-0DEC-AB80C3AF6582";
createNode decomposeMatrix -n "test_cage_anchor_7_handle_2_ctl_dcmp";
	rename -uid "7B0977D1-4F0D-6F64-380F-9991464A774A";
createNode decomposeMatrix -n "test_cage_anchor_8_ctl_dcmp";
	rename -uid "2B49221E-4FE2-41B6-31F2-2AB7E97EBB64";
createNode decomposeMatrix -n "test_cage_anchor_8_handle_0_ctl_dcmp";
	rename -uid "22719356-48D3-DDC9-F44F-2D91AD4721F9";
createNode decomposeMatrix -n "test_cage_anchor_8_handle_1_ctl_dcmp";
	rename -uid "5E050FD7-4D75-FF58-8B31-D1A44D2611CB";
createNode decomposeMatrix -n "test_cage_anchor_4_handle_2_ctl_dcmp";
	rename -uid "558B5530-4416-89FA-88F2-7E9F0C624B28";
createNode script -n "uiConfigurationScriptNode";
	rename -uid "FA95BABF-4A14-10EA-C59C-E6B8BDE866A4";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $nodeEditorPanelVisible = stringArrayContains(\"nodeEditorPanel1\", `getPanel -vis`);\n\tint    $nodeEditorWorkspaceControlOpen = (`workspaceControl -exists nodeEditorPanel1Window` && `workspaceControl -q -visible nodeEditorPanel1Window`);\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\n\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n            -shadows 0\n            -captureSequenceNumber -1\n            -width 915\n            -height 510\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n"
		+ "            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n"
		+ "            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n"
		+ "            -shadows 0\n            -captureSequenceNumber -1\n            -width 914\n            -height 509\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n"
		+ "            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n"
		+ "            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n"
		+ "            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n            -shadows 0\n            -captureSequenceNumber -1\n            -width 915\n            -height 509\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n"
		+ "        modelEditor -e \n            -camera \"|persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n"
		+ "            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n"
		+ "            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1636\n            -height 1066\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 1\n            -showReferenceMembers 1\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n"
		+ "            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -isSet 0\n            -isSetMember 0\n            -showUfeItems 1\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n"
		+ "            -longNames 0\n            -niceNames 1\n            -selectCommand \"print(\\\"\\\")\" \n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n"
		+ "            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -showUfeItems 1\n            -displayMode \"DAG\" \n"
		+ "            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n"
		+ "            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n"
		+ "                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -showUfeItems 1\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n"
		+ "                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayValues 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showPlayRangeShades \"on\" \n                -lockPlayRangeShades \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -tangentScale 1\n                -tangentLineThickness 1\n                -keyMinScale 1\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -preSelectionHighlight 0\n                -limitToSelectedCurves 0\n                -constrainDrag 0\n                -valueLinesToggle 0\n                -highlightAffectedCurves 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n"
		+ "\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 0\n"
		+ "                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -showUfeItems 1\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n"
		+ "                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayValues 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -hierarchyBelow 0\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayValues 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n"
		+ "            clipEditor -e \n                -displayValues 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n"
		+ "                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif ($nodeEditorPanelVisible || $nodeEditorWorkspaceControlOpen) {\n\t\tif (\"\" == $panelName) {\n\t\t\tif ($useSceneConfig) {\n\t\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n"
		+ "                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -connectedGraphingMode 1\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -showUnitConversions 0\n                -editorMode \"default\" \n                -hasWatchpoint 0\n                $editorName;\n\t\t\t}\n\t\t} else {\n\t\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -connectedGraphingMode 1\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n"
		+ "                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -showUnitConversions 0\n                -editorMode \"default\" \n                -hasWatchpoint 0\n                $editorName;\n\t\t\tif (!$useSceneConfig) {\n\t\t\t\tpanel -e -l $label $panelName;\n\t\t\t}\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -bluePencil 1\\n    -greasePencils 0\\n    -excludeObjectPreset \\\"All\\\" \\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1636\\n    -height 1066\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -bluePencil 1\\n    -greasePencils 0\\n    -excludeObjectPreset \\\"All\\\" \\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1636\\n    -height 1066\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "2941100E-43E6-9490-F30E-52B81A42C311";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
	setAttr ".rtfm" 1;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :standardSurface1;
	setAttr ".bc" -type "float3" 0.40000001 0.40000001 0.40000001 ;
	setAttr ".sr" 0.5;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	addAttr -ci true -h true -sn "dss" -ln "defaultSurfaceShader" -dt "string";
	setAttr ".ren" -type "string" "arnold";
	setAttr ".dss" -type "string" "standardSurface1";
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :defaultColorMgtGlobals;
	setAttr ".cfe" yes;
	setAttr ".cfp" -type "string" "K:/OCIO/aces_1.2/config.ocio";
	setAttr ".vtn" -type "string" "sRGB (ACES)";
	setAttr ".vn" -type "string" "sRGB";
	setAttr ".dn" -type "string" "ACES";
	setAttr ".wsn" -type "string" "ACES - ACEScg";
	setAttr ".otn" -type "string" "sRGB (ACES)";
	setAttr ".potn" -type "string" "sRGB (ACES)";
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape1.cp[0]";
connectAttr "test_cage_anchor_0_handle_0_ctl_dcmp.ot" "curveShape1.cp[1]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape11.cp[0]";
connectAttr "test_cage_anchor_0_handle_1_ctl_dcmp.ot" "curveShape11.cp[1]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape13.cp[0]";
connectAttr "test_cage_anchor_0_handle_2_ctl_dcmp.ot" "curveShape13.cp[1]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape29.cp[0]";
connectAttr "test_cage_anchor_0_handle_3_ctl_dcmp.ot" "curveShape29.cp[1]";
connectAttr "test_cage_anchor_1_ctl_dcmp.ot" "curveShape2.cp[0]";
connectAttr "test_cage_anchor_1_handle_0_ctl_dcmp.ot" "curveShape2.cp[1]";
connectAttr "test_cage_anchor_1_ctl_dcmp.ot" "curveShape4.cp[0]";
connectAttr "test_cage_anchor_1_handle_1_ctl_dcmp.ot" "curveShape4.cp[1]";
connectAttr "test_cage_anchor_1_ctl_dcmp.ot" "curveShape22.cp[0]";
connectAttr "test_cage_anchor_1_handle_2_ctl_dcmp.ot" "curveShape22.cp[1]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape3.cp[0]";
connectAttr "test_cage_anchor_0_handle_0_ctl_dcmp.ot" "curveShape3.cp[1]";
connectAttr "test_cage_anchor_1_handle_0_ctl_dcmp.ot" "curveShape3.cp[2]";
connectAttr "test_cage_anchor_1_ctl_dcmp.ot" "curveShape3.cp[3]";
connectAttr "test_cage_anchor_1_ctl_dcmp.ot" "curveShape6.cp[0]";
connectAttr "test_cage_anchor_1_handle_1_ctl_dcmp.ot" "curveShape6.cp[1]";
connectAttr "test_cage_anchor_2_handle_0_ctl_dcmp.ot" "curveShape6.cp[2]";
connectAttr "test_cage_anchor_2_ctl_dcmp.ot" "curveShape6.cp[3]";
connectAttr "test_cage_anchor_2_ctl_dcmp.ot" "curveShape9.cp[0]";
connectAttr "test_cage_anchor_2_handle_1_ctl_dcmp.ot" "curveShape9.cp[1]";
connectAttr "test_cage_anchor_3_handle_0_ctl_dcmp.ot" "curveShape9.cp[2]";
connectAttr "test_cage_anchor_3_ctl_dcmp.ot" "curveShape9.cp[3]";
connectAttr "test_cage_anchor_3_ctl_dcmp.ot" "curveShape12.cp[0]";
connectAttr "test_cage_anchor_3_handle_1_ctl_dcmp.ot" "curveShape12.cp[1]";
connectAttr "test_cage_anchor_0_handle_1_ctl_dcmp.ot" "curveShape12.cp[2]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape12.cp[3]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape15.cp[0]";
connectAttr "test_cage_anchor_0_handle_2_ctl_dcmp.ot" "curveShape15.cp[1]";
connectAttr "test_cage_anchor_4_handle_0_ctl_dcmp.ot" "curveShape15.cp[2]";
connectAttr "test_cage_anchor_4_ctl_dcmp.ot" "curveShape15.cp[3]";
connectAttr "test_cage_anchor_4_ctl_dcmp.ot" "curveShape18.cp[0]";
connectAttr "test_cage_anchor_4_handle_1_ctl_dcmp.ot" "curveShape18.cp[1]";
connectAttr "test_cage_anchor_5_handle_0_ctl_dcmp.ot" "curveShape18.cp[2]";
connectAttr "test_cage_anchor_5_ctl_dcmp.ot" "curveShape18.cp[3]";
connectAttr "test_cage_anchor_5_ctl_dcmp.ot" "curveShape21.cp[0]";
connectAttr "test_cage_anchor_5_handle_1_ctl_dcmp.ot" "curveShape21.cp[1]";
connectAttr "test_cage_anchor_3_handle_2_ctl_dcmp.ot" "curveShape21.cp[2]";
connectAttr "test_cage_anchor_3_ctl_dcmp.ot" "curveShape21.cp[3]";
connectAttr "test_cage_anchor_1_ctl_dcmp.ot" "curveShape24.cp[0]";
connectAttr "test_cage_anchor_1_handle_2_ctl_dcmp.ot" "curveShape24.cp[1]";
connectAttr "test_cage_anchor_6_handle_0_ctl_dcmp.ot" "curveShape24.cp[2]";
connectAttr "test_cage_anchor_6_ctl_dcmp.ot" "curveShape24.cp[3]";
connectAttr "test_cage_anchor_6_ctl_dcmp.ot" "curveShape27.cp[0]";
connectAttr "test_cage_anchor_6_handle_1_ctl_dcmp.ot" "curveShape27.cp[1]";
connectAttr "test_cage_anchor_7_handle_0_ctl_dcmp.ot" "curveShape27.cp[2]";
connectAttr "test_cage_anchor_7_ctl_dcmp.ot" "curveShape27.cp[3]";
connectAttr "test_cage_anchor_7_ctl_dcmp.ot" "curveShape30.cp[0]";
connectAttr "test_cage_anchor_7_handle_1_ctl_dcmp.ot" "curveShape30.cp[1]";
connectAttr "test_cage_anchor_0_handle_3_ctl_dcmp.ot" "curveShape30.cp[2]";
connectAttr "test_cage_anchor_0_ctl_dcmp.ot" "curveShape30.cp[3]";
connectAttr "test_cage_anchor_7_ctl_dcmp.ot" "curveShape33.cp[0]";
connectAttr "test_cage_anchor_7_handle_2_ctl_dcmp.ot" "curveShape33.cp[1]";
connectAttr "test_cage_anchor_8_handle_0_ctl_dcmp.ot" "curveShape33.cp[2]";
connectAttr "test_cage_anchor_8_ctl_dcmp.ot" "curveShape33.cp[3]";
connectAttr "test_cage_anchor_8_ctl_dcmp.ot" "curveShape36.cp[0]";
connectAttr "test_cage_anchor_8_handle_1_ctl_dcmp.ot" "curveShape36.cp[1]";
connectAttr "test_cage_anchor_4_handle_2_ctl_dcmp.ot" "curveShape36.cp[2]";
connectAttr "test_cage_anchor_4_ctl_dcmp.ot" "curveShape36.cp[3]";
connectAttr "test_cage_anchor_2_ctl_dcmp.ot" "curveShape5.cp[0]";
connectAttr "test_cage_anchor_2_handle_0_ctl_dcmp.ot" "curveShape5.cp[1]";
connectAttr "test_cage_anchor_2_ctl_dcmp.ot" "curveShape7.cp[0]";
connectAttr "test_cage_anchor_2_handle_1_ctl_dcmp.ot" "curveShape7.cp[1]";
connectAttr "test_cage_anchor_3_ctl_dcmp.ot" "curveShape8.cp[0]";
connectAttr "test_cage_anchor_3_handle_0_ctl_dcmp.ot" "curveShape8.cp[1]";
connectAttr "test_cage_anchor_3_ctl_dcmp.ot" "curveShape10.cp[0]";
connectAttr "test_cage_anchor_3_handle_1_ctl_dcmp.ot" "curveShape10.cp[1]";
connectAttr "test_cage_anchor_3_ctl_dcmp.ot" "curveShape20.cp[0]";
connectAttr "test_cage_anchor_3_handle_2_ctl_dcmp.ot" "curveShape20.cp[1]";
connectAttr "test_cage_anchor_4_ctl_dcmp.ot" "curveShape14.cp[0]";
connectAttr "test_cage_anchor_4_handle_0_ctl_dcmp.ot" "curveShape14.cp[1]";
connectAttr "test_cage_anchor_4_ctl_dcmp.ot" "curveShape16.cp[0]";
connectAttr "test_cage_anchor_4_handle_1_ctl_dcmp.ot" "curveShape16.cp[1]";
connectAttr "test_cage_anchor_4_ctl_dcmp.ot" "curveShape35.cp[0]";
connectAttr "test_cage_anchor_4_handle_2_ctl_dcmp.ot" "curveShape35.cp[1]";
connectAttr "test_cage_anchor_5_ctl_dcmp.ot" "curveShape17.cp[0]";
connectAttr "test_cage_anchor_5_handle_0_ctl_dcmp.ot" "curveShape17.cp[1]";
connectAttr "test_cage_anchor_5_ctl_dcmp.ot" "curveShape19.cp[0]";
connectAttr "test_cage_anchor_5_handle_1_ctl_dcmp.ot" "curveShape19.cp[1]";
connectAttr "test_cage_anchor_6_ctl_dcmp.ot" "curveShape23.cp[0]";
connectAttr "test_cage_anchor_6_handle_0_ctl_dcmp.ot" "curveShape23.cp[1]";
connectAttr "test_cage_anchor_6_ctl_dcmp.ot" "curveShape25.cp[0]";
connectAttr "test_cage_anchor_6_handle_1_ctl_dcmp.ot" "curveShape25.cp[1]";
connectAttr "test_cage_anchor_7_ctl_dcmp.ot" "curveShape26.cp[0]";
connectAttr "test_cage_anchor_7_handle_0_ctl_dcmp.ot" "curveShape26.cp[1]";
connectAttr "test_cage_anchor_7_ctl_dcmp.ot" "curveShape28.cp[0]";
connectAttr "test_cage_anchor_7_handle_1_ctl_dcmp.ot" "curveShape28.cp[1]";
connectAttr "test_cage_anchor_7_ctl_dcmp.ot" "curveShape31.cp[0]";
connectAttr "test_cage_anchor_7_handle_2_ctl_dcmp.ot" "curveShape31.cp[1]";
connectAttr "test_cage_anchor_8_ctl_dcmp.ot" "curveShape32.cp[0]";
connectAttr "test_cage_anchor_8_handle_0_ctl_dcmp.ot" "curveShape32.cp[1]";
connectAttr "test_cage_anchor_8_ctl_dcmp.ot" "curveShape34.cp[0]";
connectAttr "test_cage_anchor_8_handle_1_ctl_dcmp.ot" "curveShape34.cp[1]";
connectAttr "test_cage_anchor_0_srt.wm" "test_cage_anchor_0_handles.opm";
connectAttr "test_cage_anchor_0_ctl.t" "test_cage_anchor_0_handle_0_offset.t";
connectAttr "test_cage_anchor_0_ctl.r" "test_cage_anchor_0_handle_0_offset.r";
connectAttr "test_cage_anchor_0_ctl.s" "test_cage_anchor_0_handle_0_offset.s";
connectAttr "test_cage_anchor_0_ctl.t" "test_cage_anchor_0_handle_1_offset.t";
connectAttr "test_cage_anchor_0_ctl.r" "test_cage_anchor_0_handle_1_offset.r";
connectAttr "test_cage_anchor_0_ctl.s" "test_cage_anchor_0_handle_1_offset.s";
connectAttr "test_cage_anchor_0_ctl.t" "test_cage_anchor_0_handle_2_offset.t";
connectAttr "test_cage_anchor_0_ctl.r" "test_cage_anchor_0_handle_2_offset.r";
connectAttr "test_cage_anchor_0_ctl.s" "test_cage_anchor_0_handle_2_offset.s";
connectAttr "test_cage_anchor_0_ctl.t" "test_cage_anchor_0_handle_3_offset.t";
connectAttr "test_cage_anchor_0_ctl.r" "test_cage_anchor_0_handle_3_offset.r";
connectAttr "test_cage_anchor_0_ctl.s" "test_cage_anchor_0_handle_3_offset.s";
connectAttr "test_cage_anchor_1_srt.wm" "test_cage_anchor_1_handles.opm";
connectAttr "test_cage_anchor_1_ctl.t" "test_cage_anchor_1_handle_0_offset.t";
connectAttr "test_cage_anchor_1_ctl.r" "test_cage_anchor_1_handle_0_offset.r";
connectAttr "test_cage_anchor_1_ctl.s" "test_cage_anchor_1_handle_0_offset.s";
connectAttr "test_cage_anchor_1_ctl.t" "test_cage_anchor_1_handle_1_offset.t";
connectAttr "test_cage_anchor_1_ctl.r" "test_cage_anchor_1_handle_1_offset.r";
connectAttr "test_cage_anchor_1_ctl.s" "test_cage_anchor_1_handle_1_offset.s";
connectAttr "test_cage_anchor_1_ctl.t" "test_cage_anchor_1_handle_2_offset.t";
connectAttr "test_cage_anchor_1_ctl.r" "test_cage_anchor_1_handle_2_offset.r";
connectAttr "test_cage_anchor_1_ctl.s" "test_cage_anchor_1_handle_2_offset.s";
connectAttr "test_cage_anchor_2_srt.wm" "test_cage_anchor_2_handles.opm";
connectAttr "test_cage_anchor_2_ctl.t" "test_cage_anchor_2_handle_0_offset.t";
connectAttr "test_cage_anchor_2_ctl.r" "test_cage_anchor_2_handle_0_offset.r";
connectAttr "test_cage_anchor_2_ctl.s" "test_cage_anchor_2_handle_0_offset.s";
connectAttr "test_cage_anchor_2_ctl.t" "test_cage_anchor_2_handle_1_offset.t";
connectAttr "test_cage_anchor_2_ctl.r" "test_cage_anchor_2_handle_1_offset.r";
connectAttr "test_cage_anchor_2_ctl.s" "test_cage_anchor_2_handle_1_offset.s";
connectAttr "test_cage_anchor_3_srt.wm" "test_cage_anchor_3_handles.opm";
connectAttr "test_cage_anchor_3_ctl.t" "test_cage_anchor_3_handle_0_offset.t";
connectAttr "test_cage_anchor_3_ctl.r" "test_cage_anchor_3_handle_0_offset.r";
connectAttr "test_cage_anchor_3_ctl.s" "test_cage_anchor_3_handle_0_offset.s";
connectAttr "test_cage_anchor_3_ctl.t" "test_cage_anchor_3_handle_1_offset.t";
connectAttr "test_cage_anchor_3_ctl.r" "test_cage_anchor_3_handle_1_offset.r";
connectAttr "test_cage_anchor_3_ctl.s" "test_cage_anchor_3_handle_1_offset.s";
connectAttr "test_cage_anchor_3_ctl.t" "test_cage_anchor_3_handle_2_offset.t";
connectAttr "test_cage_anchor_3_ctl.r" "test_cage_anchor_3_handle_2_offset.r";
connectAttr "test_cage_anchor_3_ctl.s" "test_cage_anchor_3_handle_2_offset.s";
connectAttr "test_cage_anchor_4_srt.wm" "test_cage_anchor_4_handles.opm";
connectAttr "test_cage_anchor_4_ctl.t" "test_cage_anchor_4_handle_0_offset.t";
connectAttr "test_cage_anchor_4_ctl.r" "test_cage_anchor_4_handle_0_offset.r";
connectAttr "test_cage_anchor_4_ctl.s" "test_cage_anchor_4_handle_0_offset.s";
connectAttr "test_cage_anchor_4_ctl.t" "test_cage_anchor_4_handle_1_offset.t";
connectAttr "test_cage_anchor_4_ctl.r" "test_cage_anchor_4_handle_1_offset.r";
connectAttr "test_cage_anchor_4_ctl.s" "test_cage_anchor_4_handle_1_offset.s";
connectAttr "test_cage_anchor_4_ctl.t" "test_cage_anchor_4_handle_2_offset.t";
connectAttr "test_cage_anchor_4_ctl.r" "test_cage_anchor_4_handle_2_offset.r";
connectAttr "test_cage_anchor_4_ctl.s" "test_cage_anchor_4_handle_2_offset.s";
connectAttr "test_cage_anchor_5_srt.wm" "test_cage_anchor_5_handles.opm";
connectAttr "test_cage_anchor_5_ctl.t" "test_cage_anchor_5_handle_0_offset.t";
connectAttr "test_cage_anchor_5_ctl.r" "test_cage_anchor_5_handle_0_offset.r";
connectAttr "test_cage_anchor_5_ctl.s" "test_cage_anchor_5_handle_0_offset.s";
connectAttr "test_cage_anchor_5_ctl.t" "test_cage_anchor_5_handle_1_offset.t";
connectAttr "test_cage_anchor_5_ctl.r" "test_cage_anchor_5_handle_1_offset.r";
connectAttr "test_cage_anchor_5_ctl.s" "test_cage_anchor_5_handle_1_offset.s";
connectAttr "test_cage_anchor_6_srt.wm" "test_cage_anchor_6_handles.opm";
connectAttr "test_cage_anchor_6_ctl.t" "test_cage_anchor_6_handle_0_offset.t";
connectAttr "test_cage_anchor_6_ctl.r" "test_cage_anchor_6_handle_0_offset.r";
connectAttr "test_cage_anchor_6_ctl.s" "test_cage_anchor_6_handle_0_offset.s";
connectAttr "test_cage_anchor_6_ctl.t" "test_cage_anchor_6_handle_1_offset.t";
connectAttr "test_cage_anchor_6_ctl.r" "test_cage_anchor_6_handle_1_offset.r";
connectAttr "test_cage_anchor_6_ctl.s" "test_cage_anchor_6_handle_1_offset.s";
connectAttr "test_cage_anchor_7_srt.wm" "test_cage_anchor_7_handles.opm";
connectAttr "test_cage_anchor_7_ctl.t" "test_cage_anchor_7_handle_0_offset.t";
connectAttr "test_cage_anchor_7_ctl.r" "test_cage_anchor_7_handle_0_offset.r";
connectAttr "test_cage_anchor_7_ctl.s" "test_cage_anchor_7_handle_0_offset.s";
connectAttr "test_cage_anchor_7_ctl.t" "test_cage_anchor_7_handle_1_offset.t";
connectAttr "test_cage_anchor_7_ctl.r" "test_cage_anchor_7_handle_1_offset.r";
connectAttr "test_cage_anchor_7_ctl.s" "test_cage_anchor_7_handle_1_offset.s";
connectAttr "test_cage_anchor_7_ctl.t" "test_cage_anchor_7_handle_2_offset.t";
connectAttr "test_cage_anchor_7_ctl.r" "test_cage_anchor_7_handle_2_offset.r";
connectAttr "test_cage_anchor_7_ctl.s" "test_cage_anchor_7_handle_2_offset.s";
connectAttr "test_cage_anchor_8_srt.wm" "test_cage_anchor_8_handles.opm";
connectAttr "test_cage_anchor_8_ctl.t" "test_cage_anchor_8_handle_0_offset.t";
connectAttr "test_cage_anchor_8_ctl.r" "test_cage_anchor_8_handle_0_offset.r";
connectAttr "test_cage_anchor_8_ctl.s" "test_cage_anchor_8_handle_0_offset.s";
connectAttr "test_cage_anchor_8_ctl.t" "test_cage_anchor_8_handle_1_offset.t";
connectAttr "test_cage_anchor_8_ctl.r" "test_cage_anchor_8_handle_1_offset.r";
connectAttr "test_cage_anchor_8_ctl.s" "test_cage_anchor_8_handle_1_offset.s";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "test_cage_anchor_0_ctl.wm" "test_cage_anchor_0_ctl_dcmp.imat";
connectAttr "test_cage_anchor_0_handle_0_ctl.wm" "test_cage_anchor_0_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_1_ctl.wm" "test_cage_anchor_1_ctl_dcmp.imat";
connectAttr "test_cage_anchor_1_handle_0_ctl.wm" "test_cage_anchor_1_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_1_handle_1_ctl.wm" "test_cage_anchor_1_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_2_ctl.wm" "test_cage_anchor_2_ctl_dcmp.imat";
connectAttr "test_cage_anchor_2_handle_0_ctl.wm" "test_cage_anchor_2_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_2_handle_1_ctl.wm" "test_cage_anchor_2_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_3_ctl.wm" "test_cage_anchor_3_ctl_dcmp.imat";
connectAttr "test_cage_anchor_3_handle_0_ctl.wm" "test_cage_anchor_3_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_3_handle_1_ctl.wm" "test_cage_anchor_3_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_0_handle_1_ctl.wm" "test_cage_anchor_0_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_0_handle_2_ctl.wm" "test_cage_anchor_0_handle_2_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_4_ctl.wm" "test_cage_anchor_4_ctl_dcmp.imat";
connectAttr "test_cage_anchor_4_handle_0_ctl.wm" "test_cage_anchor_4_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_4_handle_1_ctl.wm" "test_cage_anchor_4_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_5_ctl.wm" "test_cage_anchor_5_ctl_dcmp.imat";
connectAttr "test_cage_anchor_5_handle_0_ctl.wm" "test_cage_anchor_5_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_5_handle_1_ctl.wm" "test_cage_anchor_5_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_3_handle_2_ctl.wm" "test_cage_anchor_3_handle_2_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_1_handle_2_ctl.wm" "test_cage_anchor_1_handle_2_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_6_ctl.wm" "test_cage_anchor_6_ctl_dcmp.imat";
connectAttr "test_cage_anchor_6_handle_0_ctl.wm" "test_cage_anchor_6_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_6_handle_1_ctl.wm" "test_cage_anchor_6_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_7_ctl.wm" "test_cage_anchor_7_ctl_dcmp.imat";
connectAttr "test_cage_anchor_7_handle_0_ctl.wm" "test_cage_anchor_7_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_7_handle_1_ctl.wm" "test_cage_anchor_7_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_0_handle_3_ctl.wm" "test_cage_anchor_0_handle_3_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_7_handle_2_ctl.wm" "test_cage_anchor_7_handle_2_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_8_ctl.wm" "test_cage_anchor_8_ctl_dcmp.imat";
connectAttr "test_cage_anchor_8_handle_0_ctl.wm" "test_cage_anchor_8_handle_0_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_8_handle_1_ctl.wm" "test_cage_anchor_8_handle_1_ctl_dcmp.imat"
		;
connectAttr "test_cage_anchor_4_handle_2_ctl.wm" "test_cage_anchor_4_handle_2_ctl_dcmp.imat"
		;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
// End of cage_plane_test.ma
