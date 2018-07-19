from assets import *

NOMO = AutoCar(motorLEFT, motorRIGHT)

camera = PiCamera()
camera.resolution = SIZE
camera.hflip = False
camera.vflip = True
rawCapture = PiRGBArray(camera)
time.sleep(0.5)

ArraySize = (SIZE[0], SIZE[1], 3)
X_train = np.empty(shape=ArraySize)
Y_train = np.empty(shape=(0, 2))

Stopped = False
try:
    n = 0
    for frame in camera.capture_continuous(rawCapture, format="rgb", use_video_port=True):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                Stopped = True

        image, image1 = image_correction(frame)
        rawCapture.truncate(0)
        
        NOMO.update()
        control = np.array([NOMO.read_data()])

        screen.fill((0, 0, 0))
        screen.blit(image1, (0, 0))
        pygame.display.update()

        if save_file:
            n += 1
            # Storing X and Y data
            X_train = np.append(X_train, image, axis=0)
            Y_train = np.append(Y_train, control, axis=0)
            if n % 100 == 0:
                train_x_file = "X_train{:08}.npy".format(n)
                train_y_file = "Y_train{:08}.npy".format(n)
                np.save(train_x_file, X_train)
                np.save(train_y_file, Y_train)
                transfer(train_x_file, train_y_file)

        if Stopped:
            NOMO.stop_all()
            break

except KeyboardInterrupt:
    pass

pygame.quit()
GPIO.cleanup()
