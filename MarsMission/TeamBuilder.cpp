#include "TeamBuilder.h"
#include <stdlib.h>
#include <time.h>  
#include <algorithm> 
#include <stdlib.h>
#include <time.h>   
#include <iostream>
#include "gnuplot_i.h"

TeamBuilder::TeamBuilder()
{
	srand(time(NULL));

	for (int i = 0; i < 1000; ++i)
		canidateList.push_back(Person(rand()));

	for (int i = 0; i < 50; ++i)
		teams.push_back(Team(canidateList));

	compatibility = Compatibility();

	reportTeams(true, 0);
}

std::vector<Team> TeamBuilder::createTeams(int iterations)
{
	for (int i = 0; i < iterations; ++i)
	{
		fitness();
		getBusy();
		mutate();
	}
	return teams;
}

void TeamBuilder::fitness()
{
	scoreTeams();
	deadIndecies.clear();
	purgeTheWeakAndTheHeretic(teams.size() * 0.6f, teams.size() * 0.2f);
}

void TeamBuilder::purgeTheWeakAndTheHeretic(int totalThatCanBePurged, int totalThatMustBePurged)
{
	sortTeams();
	int count = 0;
	while (deadIndecies.size() <= totalThatMustBePurged)
	{
		for (int i = 0; i < teams.size(); ++i)
		{
			if (deadIndecies.size() >= totalThatCanBePurged)
				break;

			if (teams[i].score < 0)
				deadIndecies.push_back(i);
			else if (teams[i].score < (1000 * count))
				deadIndecies.push_back(i);
		}

		count++;
	}
}

void TeamBuilder::getBusy()
{
	for (int i = 0; i < deadIndecies.size(); ++i)
	{
		int parentId1 = getIdOfRandomParent();
		int parentId2 = getIdOfRandomParent();
		while (parentId2 == parentId1)
			parentId2 = getIdOfRandomParent();

		teams[i].reborn(teams[parentId1], teams[parentId2]);
	}
}

void TeamBuilder::mutate()
{
	for (int i = 0; i < teams.size(); ++i)
	{
		for (int k = 0; k < 20; ++k)
		{
			int probablity = rand() % 100;
			if (probablity < 10)
			{
				int personListIndex = rand() % 100;
				int canidateListIndex = rand() % canidateList.size();
				teams[i].replace(canidateList[canidateListIndex], personListIndex);
			}
		}
	}
}

void TeamBuilder::reportTeams(bool isOriginal, int iterations)
{
	scoreTeams();
	sortTeams();
	int lowScore = teams[0].score;
	int highScore = teams[teams.size() - 1].score;
	int totalScore = 0;
	for (int k = 0; k < teams.size(); ++k)
		totalScore += teams[k].score;
	int average = totalScore / teams.size();

	if (isOriginal)
		std::cout << "Initial Teams:" << std::endl;
	else
		std::cout << "Iterations: " << iterations << std::endl;

	std::cout << "Lowest: " << lowScore << "  Highest: " << highScore << "  Average: " << average << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	try
	{


		///http://stackoverflow.com/questions/28892434/how-to-plot-a-graph-using-gnuplot-from-c-program

		Gnuplot g1("lines");

		//
		// Slopes
		//
		g1.set_title("Slopes\\nNew Line");
		g1.plot_slope(1.0, 0.0, "y=x");
		g1.plot_slope(2.0, 0.0, "y=2x");
		g1.plot_slope(-1.0, 0.0, "y=-x");
		g1.unset_title();

		//
		// Equations
		//
		g1.reset_plot();
		g1.plot_equation("sin(x)", "sine");
		g1.plot_equation("log(x)", "logarithm");
		g1.plot_equation("sin(x)*cos(2*x)", "sine product");

		//
		// Styles
		//
		g1.reset_plot();
		g1.set_pointsize(0.8).set_style("points");
		g1.plot_equation("sin(x)", "points");
		g1.set_style("impulses");
		g1.plot_equation("sin(x)", "impulses");
		g1.set_style("steps");
		g1.plot_equation("sin(x)", "steps");

		//
		// Save to ps
		//
		g1.reset_all();
		g1.savetofigure("test_output.ps", "postscript color");
		g1.set_style("lines").set_samples(300).set_xrange(0, 5);
		g1.plot_equation("sin(12*x)*exp(-x)").plot_equation("exp(-x)");
		g1.showonscreen(); // window output


						   //
						   // User defined 1d, 2d and 3d point sets
						   //
		std::vector<double> x, y, y2, dy, z;

		for (unsigned int i = 0; i < 50; i++)  // fill double arrays x, y, z
		{
			x.push_back((double)i);             // x[i] = i
			y.push_back((double)i * (double)i); // y[i] = i^2
			z.push_back(x[i] * y[i]);           // z[i] = x[i]*y[i] = i^3
			dy.push_back((double)i * (double)i / (double)10); // dy[i] = i^2 / 10
		}
		y2.push_back(0.00);
		y2.push_back(0.78);
		y2.push_back(0.97);
		y2.push_back(0.43);
		y2.push_back(-0.44);
		y2.push_back(-0.98);
		y2.push_back(-0.77);
		y2.push_back(0.02);


		g1.reset_all();
		g1.set_style("impulses").plot_x(y, "user-defined doubles");

		g1.reset_plot();
		g1.set_grid();
		g1.set_style("points").plot_xy(x, y, "user-defined points 2d");

		g1.reset_plot();
		g1.unset_grid();
		g1.plot_xyz(x, y, z, "user-defined points 3d");

		g1.reset_plot();
		g1.plot_xy_err(x, y, dy, "user-defined points 2d with errorbars");


		//
		// Multiple output screens
		//
		g1.reset_plot();
		g1.set_style("lines");
		g1.set_grid().set_samples(600).set_xrange(0, 300);
		g1.plot_equation("sin(x)+sin(x*1.1)");

		g1.set_xautoscale().replot();

		Gnuplot g2;
		g2.plot_x(y2, "points");
		g2.set_smooth().plot_x(y2, "cspline");
		g2.set_smooth("bezier").plot_x(y2, "bezier");
		g2.unset_smooth();

		Gnuplot g3("lines");
		g3.set_grid();
		g3.plot_equation("log(x)/x", "log(x)/x");

		Gnuplot g4("lines");
		g4.set_zrange(0, 100);
		g4.set_xlabel("x-axis").set_ylabel("y-axis").set_zlabel("z-axis");
		g4.plot_equation3d("x*x+y*y");

		Gnuplot g5("lines");
		g5.set_isosamples(25).set_hidden3d();
		g5.plot_equation3d("x*y*y");

		Gnuplot g6("lines");
		g6.set_isosamples(60).set_contour();
		g6.unset_surface().plot_equation3d("sin(x)*sin(y)+4");

		g6.set_surface().replot();

		Gnuplot g7("lines");
		g7.set_xrange(-30, 20).set_samples(40);
		g7.plot_equation("besj0(x)*0.12e1").plot_equation("(x**besj0(x))-2.5");

		g7.set_samples(400).replot();

		Gnuplot g8("filledcurves");
		g8.set_legend("outside right top").set_xrange(-5, 5);
		g8.plot_equation("x*x").plot_equation("-x*x+4");

		//
		// Plot an image
		//
		Gnuplot g9;
		const int unsigned uiWidth = 255U;
		const int unsigned uiHeight = 255U;
		g9.set_xrange(0, uiWidth).set_yrange(0, uiHeight).set_cbrange(0, 255);
		g9.cmd("set palette gray");
		unsigned char ucPicBuf[uiWidth*uiHeight];
		// generate a greyscale image
		for (unsigned int uiIndex = 0; uiIndex < uiHeight*uiWidth; uiIndex++)
		{
			ucPicBuf[uiIndex] = static_cast<unsigned char>(uiIndex % 255U);
		}
		g9.plot_image(ucPicBuf, uiWidth, uiHeight, "greyscale");

		g9.set_pointsize(0.6).unset_legend().plot_slope(0.8, 20);

		//
		// manual control
		//
		Gnuplot g10;
		g10.cmd("set samples 400").cmd("plot abs(x)/2"); // either with cmd()
		g10 << "replot sqrt(x)" << "replot sqrt(-x)";    // or with <<

	}
	catch (std::exception ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}
}

void TeamBuilder::scoreTeams()
{
	for (int i = 0; i < teams.size(); ++i)
		teams[i].scoreTeam(compatibility);
}

void TeamBuilder::demo()
{
	//for (int i = 0; i < 100000; ++i)
	//{
		fitness();
		getBusy();
		mutate();
		reportTeams(false, 1);
	//}
}

int TeamBuilder::getIdOfRandomParent()
{
	while (true)
	{
		auto randomNumber = rand() % teams.size();
		bool isDead = false;
		for (int i = 0; i < deadIndecies.size(); ++i)
		{
			if (deadIndecies[i] == randomNumber)
			{
				isDead = true;
				break;
			}
		}

		if (!isDead)
		{
			return randomNumber;
		}
	}
}

void TeamBuilder::sortTeams()
{
	std::sort(teams.begin(), teams.end(), [](const Team& lhs, const Team& rhs)
	{
		return lhs.score < rhs.score;
	});
}
