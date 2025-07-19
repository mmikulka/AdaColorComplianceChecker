#ifndef ADACOMPLIANCECHECKER_H
#define ADACOMPLIANCECHECKER_H

#include <QColor>

class ADAComplianceChecker
{
public:
    ADAComplianceChecker();

    ~ADAComplianceChecker() = default;

    ADAComplianceChecker(const ADAComplianceChecker&) = delete;
    ADAComplianceChecker(ADAComplianceChecker&&) = delete;
    ADAComplianceChecker operator=(ADAComplianceChecker&) = delete;

    /**
     * @brief Calculate Constrast Ratio of the two Values
     * @param foreground color RGB
     * @param Background color RGB
     * @return
     */
    static double CalculateConstrastRatio(const QColor &foreground,
                                const QColor &Background);

private:

    /**
     * @brief Normalizes color value
     * @param value: color value
     * @return normalized color value
     */
    static double normalize(const int value);

    /**
     * @brief calculate Relative Luminance of RGB color
     * @param RGB color to calculate luminance over
     * @return luminance value of RGB color
     */
    static double calculateRelativeLuminance(const QColor& color);
};

#endif // ADACOMPLIANCECHECKER_H
