(define (problem gripper3_5_balls)
	(:domain gripper3)

	(:objects
		rooma roomb - room
		ball1 ball2 ball3 ball4 ball5 - ball)

	(:init
		(free left)
		(free right)
		(at-robby rooma)
		(at-ball ball1 rooma)
		(at-ball ball2 rooma)
		(at-ball ball3 rooma)
		(at-ball ball4 rooma)
		(at-ball ball5 rooma)
		(whole ball1)
		(whole ball2)
		(whole ball3)
		(whole ball4)
		(whole ball5)
	)

	(:goal
		(and
			(at-ball ball1 roomb)
			(at-ball ball2 roomb)
			(at-ball ball3 roomb)
			(at-ball ball4 roomb)
			(at-ball ball5 roomb)
			(whole ball1)
			(whole ball2)
			(whole ball3)
			(whole ball4)
			(whole ball5)
			(at-robby roomb)
		)
	)
)
