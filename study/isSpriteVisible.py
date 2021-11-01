import math

tab3Sin, tab3Cos = [] , []

def toFixAngle(angle_radian):
    return angle_radian*128/math.pi

def main ():
    objPosX, objPosY = 0, 0
    camPosX, camPosY = 2, 1
    camRotZ = math.radians(-180)

    objAlpha = math.atan2(objPosY-camPosY, objPosX-camPosX)
    beta = objAlpha+math.radians(90)
    print (f'Alpha = {math.degrees(objAlpha)}, Beta= {math.degrees(beta)}, ')


    objAx, objAy = objPosX + 3*math.cos(beta), objPosY + 3*math.sin(beta)
    objBx, objBy = objPosX - 3*math.cos(beta), objPosY - 3*math.sin(beta)

    alphaA = math.atan2(objAy-camPosY, objAx-camPosX)
    alphaB = math.atan2(objBy-camPosY, objBx-camPosX)
    angleA = alphaA - camRotZ
    angleB = alphaB - camRotZ
    print (f'A ({objAx},{objAy}) {math.degrees(alphaA)} {math.degrees(angleA)},\n B ({objBx},{objBy}) {math.degrees(alphaB)} {math.degrees(angleB)}')

def genTab3Trigo():
    global tab3Sin, tab3Cos
    tab3Sin, tab3Cos = [] , []
    for angle in range (256):
        v= int.from_bytes(bytes([angle]), byteorder='big', signed=True)
        tab3Sin.append(round(3*math.sin(v*math.pi/128)))
        tab3Cos.append(round(3*math.cos(v*math.pi/128)))
    return tab3Sin, tab3Cos
     

if __name__ == "__main__":
    # execute only if run as a script
    print (genTab3Trigo())
    main()    
