

REM [ref lookup_generate]
python tools\precalDistance2Height.py > proto\c\tabunlogd2hh.h
python tools\precalcTabMulti.py > proto\c\tabMulti.h
python tools\precalcUnfish.py > proto\c\tabunfish.h
python tools\precalcLogTrigo.py > proto\c\tablogtrigo.h
python tools\precalcRayAngle.py > proto\c\tabrayangle.h

python tools\precalcTextureIndex.py > proto\c\tabIdxRdTexture.h
python tools\precalcIdxOfIdxRd.py > proto\c\tabAdrTabIdxRd.h

REM [ref config_viewport]
REM python tools\clearViewport.py > proto\c\viewport_s.s
python tools\clearVertColBuf.py > proto\c\vertcolbuf_s.s
python tools\copyVertColBuf.py >> proto\c\vertcolbuf_s.s
REM python tools\clearColumn.py > proto\c\column_s.s

REM [ref texel_codec]
python tools\precalcTexel.py > proto\c\tabTexelColor.h

REM [ref config_generate]
python tools\generateConstants.py > proto\c\constants.h

REM [ref texture_file2buffer]
python tools\texture2buf.py img\bluestone.png > proto\c\texture_bluestone.h
python tools\texture2buf.py img\logo.png > proto\c\texture_logo.h
python tools\texture2buf.py img\redbrick.png > proto\c\texture_redbrick.h
python tools\texture2buf.py img\christmas.bmp > proto\c\texture_christmas.h
python tools\texture2buf.py img\aKey.bmp > proto\c\texture_key.h
python tools\texture2buf.py img\pillar.bmp > proto\c\texture_pillar.h

python tools\texture2buf.py img\smily_back.bmp > proto\c\texture_sback.h
python tools\texture2buf.py img\smily_front.bmp > proto\c\texture_sfront.h
python tools\texture2buf.py img\smily_left.bmp > proto\c\texture_sleft.h
python tools\texture2buf.py img\smily_right.bmp > proto\c\texture_sright.h

python tools\texture2buf.py img\soldier_back.bmp > proto\c\texture_sback.h
python tools\texture2buf.py img\soldier_front.bmp > proto\c\texture_sfront.h
python tools\texture2buf.py img\soldier_left.bmp > proto\c\texture_sleft.h
python tools\texture2buf.py img\soldier_right.bmp > proto\c\texture_sright.h


python tools\texture2buf.py img\tree.png > proto\c\texture_tree.h
